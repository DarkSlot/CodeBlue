// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "StationInfoDataItem.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FStationInfoDataItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 UserId;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	float FoodCost;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	float FuelCost;

	FStationInfoDataItem() {
		UserId = 0;
		FoodCost = 0.0f;
		FuelCost = 0.0f;
	}
	FStationInfoDataItem(int32 uid, float food, float fuel) {
		UserId = uid;
		FoodCost = food;
		FuelCost = fuel;
	}
	FStationInfoDataItem(const FStationInfoDataItem &item) {
		UserId = item.UserId;
		FoodCost = item.FoodCost;
		FuelCost = item.FuelCost;
	}
};
//Key is station id
typedef TMap<int32, FStationInfoDataItem *> StationInfoList;
//typedef TMultiMap<int32, FStationInfoDataItem *> StationTradeList;