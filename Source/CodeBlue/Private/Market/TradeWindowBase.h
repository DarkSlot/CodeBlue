// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "TradeWindowBase.generated.h"

/**
 * 
 */
UCLASS()
class UTradeWindowBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Market")
	void UpdateTradeWindow(const int32 productid,const bool IsBuyWindow);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Market")
	void InitTradeWindow(const FText &ProductName,const float AdvisePrice);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market")
	int32 ProductId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market")
	bool bIsBuyWindow;
};
