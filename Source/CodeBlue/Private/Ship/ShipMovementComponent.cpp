// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ShipMovementComponent.h"


#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/WorldSettings.h"

UShipMovementComponent::UShipMovementComponent()
{
	MaxSpeed = 1200.f;
	Acceleration = 4000.f;
	Deceleration = 8000.f;
	bPositionCorrected = false;
	bUseAccelerationForPaths = true;

	bNoBackforwardMove = false;

	bConstrainToPlane = true;
	SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);

	ResetMoveState();
}

void UShipMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}

	const AController* Controller = PawnOwner->GetController();
	if (Controller && Controller->IsLocalController())
	{
		// apply input for local players but also for AI that's not following a navigation path at the moment
		if (Controller->IsLocalPlayerController() == true || Controller->IsFollowingAPath() == false || bUseAccelerationForPaths)
		{
			ApplyControlInputToVelocity(DeltaTime);
		}
		// if it's not player controller, but we do have a controller, then it's AI
		// (that's not following a path) and we need to limit the speed
		else if (IsExceedingMaxSpeed(MaxSpeed) == true)
		{
			Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
		}

		LimitWorldBounds();
		bPositionCorrected = false;

		// Move actor
		FVector Delta = Velocity * DeltaTime;

		if (!Delta.IsNearlyZero(1e-6f))
		{
			const FVector OldLocation = UpdatedComponent->GetComponentLocation();
			const FQuat Rotation = UpdatedComponent->GetComponentQuat();

			FHitResult Hit(1.f);
			SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);

			if (Hit.IsValidBlockingHit())
			{
				HandleImpact(Hit, DeltaTime, Delta);
				// Try to slide the remaining distance along the surface.
				SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
			}

			// Update velocity
			// We don't want position changes to vastly reverse our direction (which can happen due to penetration fixups etc)
			if (!bPositionCorrected)
			{
				const FVector NewLocation = UpdatedComponent->GetComponentLocation();
				Velocity = ((NewLocation - OldLocation) / DeltaTime);
			}
		}

		// Finalize
		UpdateComponentVelocity();
	}
};

bool UShipMovementComponent::LimitWorldBounds()
{
	AWorldSettings* WorldSettings = PawnOwner ? PawnOwner->GetWorldSettings() : NULL;
	if (!WorldSettings || !WorldSettings->bEnableWorldBoundsChecks || !UpdatedComponent)
	{
		return false;
	}

	const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
	if (CurrentLocation.Z < WorldSettings->KillZ)
	{
		Velocity.Z = FMath::Min(GetMaxSpeed(), WorldSettings->KillZ - CurrentLocation.Z + 2.0f);
		return true;
	}

	return false;
}

void UShipMovementComponent::ApplyControlInputToVelocity(float DeltaTime)
{
	FVector InputDir = GetPendingInputVector();
	const float AnalogInputModifier = (InputDir.SizeSquared() > 0.f ? InputDir.Size() : 0.f);
	if (AnalogInputModifier>0.0f)
	{
		FVector MoveDir = InputDir;
		if (PawnOwner)
		{
			FVector forward = PawnOwner->GetActorForwardVector();
			if (bNoBackforwardMove||FVector::DotProduct(forward, InputDir)>0.0f)
			{
				MoveDir = forward;
			}
			else
			{
				MoveDir = -forward;
			}
		}
		else
		{
			MoveDir.Normalize();
		}
		FVector effectvel(0.0f,0.0f,0.0f);
		float CurrentSpeed = Velocity.Size();
		if (CurrentSpeed>0.0f)
		{
			FVector NormalizedVel = Velocity / CurrentSpeed;
			float cosalpha = FVector::DotProduct(MoveDir, NormalizedVel);
			float MoveSpeed = MaxSpeed;
			if (FMath::Abs(cosalpha)>0.001f)
			{
				MoveSpeed = CurrentSpeed / cosalpha;
				MoveSpeed = FMath::Min(MaxSpeed, MoveSpeed);
			}
			if (cosalpha>=0.0f)
			{
				MoveSpeed += AnalogInputModifier* Acceleration * DeltaTime;
			}
			else
			{
				MoveSpeed += AnalogInputModifier* (Acceleration + Deceleration) * DeltaTime;
			}
			MoveSpeed = FMath::Min(MaxSpeed, MoveSpeed);
			effectvel = MoveSpeed * MoveDir;
		}
		else
		{
			effectvel+= MoveDir *AnalogInputModifier*Acceleration * DeltaTime;
		}
		effectvel.Z = 0.0f;

		Velocity = effectvel;
	}
	else
	{
		if (Velocity.SizeSquared() > 0.f)
		{
			const float VelSize = FMath::Max(Velocity.Size() - FMath::Abs(Deceleration) * DeltaTime, 0.f);
			Velocity = Velocity.GetSafeNormal() * VelSize;
		}
	}
	ConsumeInputVector();
}
bool UShipMovementComponent::ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotationQuat)
{
	bPositionCorrected |= Super::ResolvePenetrationImpl(Adjustment, Hit, NewRotationQuat);
	return bPositionCorrected;
}

