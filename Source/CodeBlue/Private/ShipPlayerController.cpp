// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ShipPlayerController.h"
#include "ShipPawnBase.h"

const FName AShipPlayerController::MoveForwardBinding("MoveForwardBinding");
const FName AShipPlayerController::TurnRightBinding("TurnRightBinding");

AShipPlayerController::AShipPlayerController() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
void AShipPlayerController::DockShip() {

}

void AShipPlayerController::SetupInputComponent() {
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATopdownPlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &ATopdownPlayerController::OnSetDestinationReleased);

	//// support touch devices 
	//InputComponent->BindAction("SetDestination", this, &ATopdownPlayerController::MoveToTouchLocation);
	
	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(TurnRightBinding);
}
void AShipPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(TurnRightBinding);

	if (ForwardValue==0.0f&& RightValue==0.0f)
	{
		return;
	}

	AShipPawnBase *pawn = Cast<AShipPawnBase>(GetPawn());
	FVector ForwardDir = pawn->GetActorForwardVector();
	FRotator PawnRotator = pawn->GetActorRotation();
	const FVector Movement = ForwardDir * ForwardValue *DeltaTime*pawn->Speed;
	PawnRotator.Yaw += RightValue*DeltaTime*pawn->Agility;

	FHitResult Hit;
	pawn->GetRootComponent()->MoveComponent(Movement, PawnRotator, true, &Hit);
	if (Hit.IsValidBlockingHit())
	{
		const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
		const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
		pawn->GetRootComponent()->MoveComponent(Deflection, PawnRotator, true);
	}
}
