// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "../Station/StationPanelBase.h"
#include "ShipPlayerController.generated.h"

/**
 * 
 */
class AStationBase;
UCLASS()
class AShipPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	AShipPlayerController();

	UFUNCTION(BlueprintCallable, Category = Ship)
	bool DockShip();

	UFUNCTION(BlueprintCallable, Category = Ship)
	bool UndockShip();
	
	/** this ship is docking. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ship)
	bool bDocking;

	/** The docing station of this ship. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Ship)
	AStationBase  *DockingStation;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UStationPanelBase* DockingStationPanel;
protected:
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime);
	
	static const FName MoveForwardBinding;
	static const FName TurnRightBinding;

	void OnFirePressed();
	void OnFireReleased();
};
