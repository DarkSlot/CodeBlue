// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "PropertyDataItem.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FPropertyDataItem
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(BlueprintReadOnly, Category = "Data")
	bool unsaved;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 propertyid;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 userid;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 stationid;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 productid;
	
	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 num;

	FPropertyDataItem()
		:unsaved(true),
		propertyid(0),
		userid(0),
		stationid(0),
		productid(0),
		num(0)
	{
	}

	FPropertyDataItem(int32 user, int32 station, int32 product)
		:unsaved(true),
		propertyid(0),
		userid(user),
		stationid(station),
		productid(product),
		num(0)
	{
	}
};
//key is productid
typedef TMap<int32, FPropertyDataItem> PropertyList;
//key is stationid
typedef TMap<int32, PropertyList> StationPropertyList;
//key is userid
typedef TMap<int32, StationPropertyList> UserPropertyList;