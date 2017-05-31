// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "UserDataTable.generated.h"
/**
 * 
 */
USTRUCT(Blueprintable)
struct FUserDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** Full Path of Blueprint */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 userid;

	/** Category of GamePlay Object */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	FString username;

	/** Scriptable Use Code */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	FString description;

	/** Scriptable Use Code */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 usertype;

	/** Scriptable Use Code */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	int32 money;
};
