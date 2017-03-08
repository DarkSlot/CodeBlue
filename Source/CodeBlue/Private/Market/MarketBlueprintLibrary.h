// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MarketBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UMarketBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Market")
	static void BuyProduct(const int32 productid, const float price, const int32 num,
		const int32 userid, const int32 depotid);
	
	UFUNCTION(BlueprintCallable, Category = "Market")
	static void SellProduct(const int32 productid, const float price, const int32 num,
		const int32 userid, const int32 depotid);

	UFUNCTION(BlueprintCallable, Category = "Util")
	static FString VerifyFloatString(const FString &Str);

	UFUNCTION(BlueprintCallable, Category = "Util")
	static FString VerifyIntString(const FString &Str);
};
