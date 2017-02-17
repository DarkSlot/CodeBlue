// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "MainMarketFrameBase.generated.h"

/**
 * 
 */
UCLASS()
class UMainMarketFrameBase : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "Market")
	void UpdateList(FName MarketName);

	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void ClearOrderList();

	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void AddProductMenuItem(const FText &ProductName,const int32 ProductId);
	
	UFUNCTION(BlueprintCallable, Category = "Market")
	void UpdateOrderList(const int32 order);

	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void AddSellOrderItem(const float price,const int32 stock);

	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void AddBuyOrderItem(const float price, const int32 stock);
};
