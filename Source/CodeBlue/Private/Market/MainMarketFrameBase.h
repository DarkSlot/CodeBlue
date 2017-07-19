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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market")
	int32 CurrentProductId;

	UFUNCTION(BlueprintCallable, Category = "Market")
	void UpdateList();

	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void ClearOrderList();

	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void AddProductMenuItem(const FText &ProductName,const int32 ProductId);
	
	UFUNCTION(BlueprintCallable, Category = "Market")
	void UpdateOrderList(const int32 product,const int32 station);

	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void AddSellOrderItem(const float price,const int32 stock,const FString &updatetime);

	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void AddBuyOrderItem(const float price, const int32 stock, const FString &updatetime);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Station")
	int32 StationId;
private:
	FString GetProductNameById(const int32 productid);
};
