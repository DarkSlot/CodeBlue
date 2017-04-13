// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "ProductDataTable.generated.h"

USTRUCT(Blueprintable)
struct FProductDataTable : public FTableRowBase
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
};