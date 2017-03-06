// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MarketBlueprintLibrary.h"
#include "UnrealString.h"

void UMarketBlueprintLibrary::BuyProduct(const int32 ProductId, const int32 price, const int32 num) {
}
void UMarketBlueprintLibrary::SellProduct(const int32 ProductId, const int32 price, const int32 num) {

}
FString UMarketBlueprintLibrary::VerifyPriceString(const FString &Str) {
	FString result(TEXT(""));
	int len = Str.Len();
	for (int i = 0; i < len; i++)
	{
		if ((i==0&&Str[i]>='1'&&Str[i]<='9')||(i> 0&&((Str[i] >= '0'&&Str[i]<='9')||Str[i] == '.')))
		{
			result.AppendChar(Str[i]);
		}
	}
	return result;
}