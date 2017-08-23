// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "ShipSaveDataItem.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FShipSaveDataItem
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(BlueprintReadWrite, Category = "Save")
	FVector Position;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	FRotator Rotation;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	FVector Velocity;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	int32 Hitpoint;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	int32 HitpointMax;

	FShipSaveDataItem()
	{
	}
};