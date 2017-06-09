// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "ProduceLineDataItem.generated.h"

USTRUCT(Blueprintable)
struct FProduceLineDataItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 ProductId;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 UserId;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 StationId;

	FProduceLineDataItem() {
		ProductId = 0;
		UserId = 0;
		StationId = 0;
	}
	FProduceLineDataItem(const FProduceLineDataItem &table) {
		ProductId = table.ProductId;
		UserId = table.UserId;
		StationId = table.StationId;
	}
	FProduceLineDataItem operator=(const FProduceLineDataItem &table) {
		FProduceLineDataItem result;
		result.ProductId = table.ProductId;
		result.UserId = table.UserId;
		result.StationId = table.StationId;
		return result;
	}
};