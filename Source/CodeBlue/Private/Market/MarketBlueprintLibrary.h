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
	static void BuyProduct(const int32 ProductId,const int32 price,const int32 num);
	
	UFUNCTION(BlueprintCallable, Category = "Market")
	static void SellProduct(const int32 ProductId, const int32 price, const int32 num);

	UFUNCTION(BlueprintCallable, Category = "Market")
	static FString VerifyPriceString(const FString &Str);
};
