// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ShipPawnBase.generated.h"

UCLASS()
class CODEBLUE_API AShipPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	/** The speed of this ship. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
	float Speed;

	/** The Agility of this ship. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
	float Agility;
};
