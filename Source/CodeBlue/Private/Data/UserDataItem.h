// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "UserDataItem.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FUserDataItem : public FTableRowBase
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
	
	UPROPERTY(BlueprintReadWrite, Category = "Data")
	float money;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 AIType;

	FUserDataItem():
		userid(0),
		username(""),
		description(""),
		usertype(0),
		money(0.0f),
		AIType(0){

	}
	FUserDataItem(const FUserDataItem& item) :
		userid(item.userid),
		username(item.username),
		description(item.description),
		usertype(item.usertype),
		money(item.money),
		AIType(item.AIType) {

	}
};
typedef TMap<int32, FUserDataItem> UserList;