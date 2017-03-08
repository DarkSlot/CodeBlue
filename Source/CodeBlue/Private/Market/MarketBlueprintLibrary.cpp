// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MarketBlueprintLibrary.h"
#include "UnrealString.h"
#include "MarketProcessCore.h"
#include "Command/BuyProductCommand.h"
#include "Command/SellProductCommand.h"

void UMarketBlueprintLibrary::BuyProduct(const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 depotid) {
	BuyProductCommand *command = new BuyProductCommand(productid,price,num,userid,depotid);
	MarketProcessCore::StartGetInstance()->EnqueueCommand(command);
}
void UMarketBlueprintLibrary::SellProduct(const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 depotid) {
	SellProductCommand *command = new SellProductCommand(productid, price, num, userid, depotid);
	MarketProcessCore::StartGetInstance()->EnqueueCommand(command);
}
FString UMarketBlueprintLibrary::VerifyFloatString(const FString &Str) {
	FString result(TEXT(""));
	int len = Str.Len();
	bool havedot = false;

	for (int i = 0; i < len; i++)
	{
		if (result.Len() == 0)
		{
			if ((Str[i] >= '1'&&Str[i] <= '9')||(i+1<len&&Str[i]=='0'&&Str[i+1]=='.'))
			{
				result.AppendChar(Str[i]);
			}
		}
		else if (Str[i] >= '0'&&Str[i]<='9')
		{
			result.AppendChar(Str[i]);
		}
		else if (!havedot&&Str[i] == '.')
		{
			result.AppendChar(Str[i]);
			havedot = true;
		}
	}
	return result;
}
FString UMarketBlueprintLibrary::VerifyIntString(const FString &Str) {
	FString result(TEXT(""));
	int len = Str.Len();
	for (int i = 0; i < len; i++)
	{
		if ((result.Len() == 0 && Str[i] >= '1'&&Str[i] <= '9') || (result.Len()> 0 && (Str[i] >= '0'&&Str[i] <= '9') ))
		{
			result.AppendChar(Str[i]);
		}
	}
	return result;
}
