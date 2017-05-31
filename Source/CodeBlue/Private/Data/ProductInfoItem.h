// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "ProductDataTable.generated.h"

USTRUCT(Blueprintable)
struct FProductInfoItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** Full Path of Blueprint */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 productid;

	/** Category of GamePlay Object */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	FString productname;

	/** Scriptable Use Code */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	FString description;

	/** Scriptable Use Code */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	float baseprice;

	FProductInfoItem() {
		productid = 0;
		productname = TEXT("");
		description = TEXT("");
		baseprice = 0.0f;
	}
	FProductInfoItem(const FProductInfoItem &table) {
		productid = table.productid;
		productname = table.productname;
		description = table.description;
		baseprice = table.baseprice;
	}
	FProductInfoItem operator=(const FProductInfoItem &table) {
		FProductInfoItem result;
		result.productid = table.productid;
		result.productname = table.productname;
		result.description = table.description;
		result.baseprice = table.baseprice;
		return result;
	}
};