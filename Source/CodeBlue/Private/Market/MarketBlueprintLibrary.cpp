// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MarketBlueprintLibrary.h"
#include "UnrealString.h"
#include "../GMGameInstance.h"
#include "../Data/DataProcesser.h"

void UMarketBlueprintLibrary::BuyProduct(const UObject *WorldContext,
	const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 stationid) {
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(UGameplayStatics::GetGameInstance(WorldContext));
	GameInstance->DataProcesser->BuyProduct(productid, price,num,userid, stationid);
}
void UMarketBlueprintLibrary::SellProduct(const UObject *WorldContext,
	const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 stationid) {
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(UGameplayStatics::GetGameInstance(WorldContext));
	GameInstance->DataProcesser->SellProduct(productid, price, num, userid, stationid);
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
