// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ShipPlayerController.generated.h"

/**
 * 
 */
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
	
	/** The Agility of this ship. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ship)
		bool bDocking;
protected:
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime);
	
	static const FName MoveForwardBinding;
	static const FName TurnRightBinding;
};
