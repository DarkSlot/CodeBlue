// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "StationTradeDataItem.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FStationTradeDataItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 userid;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 product;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 isBuy;

	FStationTradeDataItem() {
		userid = 0;
		product = 0;
		isBuy = 0;
	}
	FStationTradeDataItem(const FStationTradeDataItem &item) {
		userid = item.userid;
		product = item.product;
		isBuy = item.isBuy;
	}
};
//Key is station id
typedef TMultiMap<int32, FStationTradeDataItem *> StationTradeList;