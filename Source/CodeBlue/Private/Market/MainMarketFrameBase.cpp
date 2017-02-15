// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MainMarketFrameBase.h"
#include "../Localization/ProductLocalizationList.h"
#include "SQLiteDatabase.h"

void UMainMarketFrameBase::UpdateList(FName MarketName) {
	USQLiteDatabase::RegisterDatabase(TEXT("market"), TEXT("/Data/market.db"),true);
	FString product_sql = TEXT("select * from product");
	FSQLiteQueryResult result = USQLiteDatabase::GetData(TEXT("market"), product_sql);
	if (result.Success)
	{
		for (auto &row: result.ResultRows)
		{
			for (auto &item : row.Fields)
			{
				if (item.Key == TEXT("productname"))
				{
					FText TestHUDText = FText::FromString(item.Value);
					AddProductMenuItem(ProductLocalizationList::FindProductName(item.Value));
				}
			}
		}
	}
	//AddProductItem(TEXT("adfasdfsalk"));
	//FText TestHUDText = NSLOCTEXT("Your Namespace", "Your Key", "≤‚ ‘");
	//AddProductMenuItem(TestHUDText);
}


