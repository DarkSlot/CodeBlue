// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Data/StationInfoDataItem.h"
#include "Buff/BuffStarving.h"
#include "StationBase.generated.h"

class UDataProcesser;
UCLASS()
class CODEBLUE_API AStationBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStationBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Station")
	int32 StationId;

	UPROPERTY(BlueprintReadOnly, Category = "Station")
	float FoodCost;

	UPROPERTY(BlueprintReadOnly, Category = "Station")
	float FuelCost;

	float CostTimer;

	UDataProcesser *DataProcesser;

	BuffStarving m_BuffStarving;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DealFoodShortage(int32 starvinglvl);
};
