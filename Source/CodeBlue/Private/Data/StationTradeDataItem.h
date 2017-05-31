// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "UserDataItem.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FUserDataItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 userid;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	FString username;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	FString description;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 usertype;
	
	UPROPERTY(BlueprintReadOnly, Category = "Data")
	float money;
};
typedef TMap<int32, FUserDataItem> UserList;