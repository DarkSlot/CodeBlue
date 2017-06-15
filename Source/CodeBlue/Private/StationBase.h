// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Data/StationInfoDataItem.h"
#include "StationBase.generated.h"

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Station")
	int32 StationId;

	UPROPERTY(BlueprintReadOnly, Category = "Station")
	float FoodCost;

	UPROPERTY(BlueprintReadOnly, Category = "Station")
	float FuelCost;
};
