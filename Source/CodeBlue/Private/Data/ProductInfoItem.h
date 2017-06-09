// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "ProductInfoItem.generated.h"

USTRUCT(Blueprintable)
struct FProductInfoItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 productid;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	FString productname;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	FString description;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	float baseprice;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	float BaseTime;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	float BaseProduction;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 RawMaterial0;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	float Cost0;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 RawMaterial1;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	float Cost1;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 RawMaterial2;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	float Cost2;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 RawMaterial3;

	UPROPERTY(BlueprintReadOnly, Category = "Market")
	float Cost3;

	FProductInfoItem() {
		productid = 0;
		productname = TEXT("");
		description = TEXT("");
		baseprice = 0.0f;
		BaseTime = 0.0f;
		BaseProduction = 0.0f;
		RawMaterial0 = 0;
		Cost0 = 0.0f;
		RawMaterial1 = 0;
		Cost1 = 0.0f;
		RawMaterial2 = 0;
		Cost2 = 0.0f;
		RawMaterial3 = 0;
		Cost3 = 0.0f;
	}
	FProductInfoItem(const FProductInfoItem &table) {
		productid = table.productid;
		productname = table.productname;
		description = table.description;
		baseprice = table.baseprice;
		BaseTime = table.BaseTime;
		BaseProduction = table.BaseProduction;
		RawMaterial0 = table.RawMaterial0;
		Cost0 = table.Cost0;
		RawMaterial1 = table.RawMaterial1;
		Cost1 = table.Cost1;
		RawMaterial2 = table.RawMaterial2;
		Cost2 = table.Cost2;
		RawMaterial3 = table.RawMaterial3;
		Cost3 = table.Cost3;
	}
	FProductInfoItem operator=(const FProductInfoItem &table) {
		FProductInfoItem result;
		result.productid = table.productid;
		result.productname = table.productname;
		result.description = table.description;
		result.baseprice = table.baseprice;
		result.BaseTime = table.BaseTime;
		result.BaseProduction = table.BaseProduction;
		result.RawMaterial0 = table.RawMaterial0;
		result.Cost0 = table.Cost0;
		result.RawMaterial1 = table.RawMaterial1;
		result.Cost1 = table.Cost1;
		result.RawMaterial2 = table.RawMaterial2;
		result.Cost2 = table.Cost2;
		result.RawMaterial3 = table.RawMaterial3;
		result.Cost3 = table.Cost3;
		return result;
	}
};