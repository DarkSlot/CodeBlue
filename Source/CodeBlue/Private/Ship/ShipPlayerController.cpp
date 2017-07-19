// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ShipPlayerController.h"
#include "ShipPawnBase.h"

const FName AShipPlayerController::MoveForwardBinding("MoveForwardBinding");
const FName AShipPlayerController::TurnRightBinding("TurnRightBinding");

AShipPlayerController::AShipPlayerController() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bDocking = false;
}

bool AShipPlayerController::DockShip() {
	if (bDocking)
	{
		return false;
	}
	UObject* tAsset = LoadObject<UClass>(nullptr, TEXT("/Game/UI/Station/StationPanel.StationPanel_C"));
	if (!tAsset) return false;
	UClass* bp = Cast<UClass>(tAsset);
	if (!bp) return false;
	UUserWidget *panel = CreateWidget<UUserWidget>(this, bp);
	DockingStationPanel = Cast<UStationPanelBase>(panel);
	DockingStationPanel->AddToViewport();
	DockingStationPanel->CurrentStation = DockingStation;
	DockingStationPanel->InitStationInfo();
	bDocking = true;
	return true;
}
bool AShipPlayerController::UndockShip() {
	if (!bDocking)
	{
		return false;
	}
	DockingStationPanel->RemoveFromParent();
	bDocking = false;
	return true;
}
void AShipPlayerController::SetupInputComponent() {
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Fire", IE_Pressed, this, &AShipPlayerController::OnFirePressed);
	InputComponent->BindAction("Fire", IE_Released, this, &AShipPlayerController::OnFireReleased);

	//// support touch devices 
	//InputComponent->BindAction("SetDestination", this, &ATopdownPlayerController::MoveToTouchLocation);
	
	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(TurnRightBinding);
}
void AShipPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);
	if (bDocking)
	{
		return;
	}
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(TurnRightBinding);

	if (ForwardValue==0.0f&& RightValue==0.0f)
	{
		return;
	}

	AShipPawnBase *pawn = Cast<AShipPawnBase>(GetPawn());
	if (pawn)
	{
		FVector ForwardDir = pawn->GetActorForwardVector();
		FRotator PawnRotator = pawn->GetActorRotation();
		const FVector Movement = ForwardDir * ForwardValue *DeltaTime*pawn->Speed;
		PawnRotator.Yaw += RightValue*DeltaTime*pawn->Agility;

		FHitResult Hit(1.0f);
		pawn->GetRootComponent()->MoveComponent(Movement, PawnRotator, true, &Hit);
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			pawn->GetRootComponent()->MoveComponent(Deflection, PawnRotator, true);
		}
	}
}
void AShipPlayerController::OnFirePressed() {
	AShipPawnBase *pawn = Cast<AShipPawnBase>(GetPawn());
	if (pawn)
	{
		pawn->StartFireWeapon();
	}
}
void AShipPlayerController::OnFireReleased() {
	AShipPawnBase *pawn = Cast<AShipPawnBase>(GetPawn());
	if (pawn)
	{
		pawn->StopFireWeapon();
	}
}
