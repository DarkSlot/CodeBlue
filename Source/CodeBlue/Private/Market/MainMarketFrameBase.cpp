// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MainMarketFrameBase.h"
#include "../Localization/ProductLocalizationList.h"
#include "SQLiteDatabase.h"

void UMainMarketFrameBase::UpdateList(FName MarketName) {
	FString product_sql = TEXT("select * from product");
	FSQLiteQueryResult result = USQLiteDatabase::GetData(TEXT("market"), product_sql);
	if (result.Success)
	{
		for (auto &row: result.ResultRows)
		{
			FString name = "";
			int32 productid = 0;
			for (auto &item : row.Fields)
			{
				if (item.Key == TEXT("productname"))
				{
					name = item.Value;
				}
				else if (item.Key == TEXT("productid"))
				{
					productid = FCString::Atoi(*item.Value);
				}
			}
			AddProductMenuItem(ProductLocalizationList::FindProductName(name), productid);
		}
	}
}
void UMainMarketFrameBase::UpdateOrderList(const int32 order) {
	ClearOrderList();
	FString product_sql = TEXT("select * from ProductOrder where productid =");
	product_sql.AppendInt(order);
	FSQLiteQueryResult result = USQLiteDatabase::GetData(TEXT("market"), product_sql);
	if (result.Success)
	{
		for (auto &row : result.ResultRows)
		{
			int32 ordertype = 0;
			int32 userid = 0;
			int32 stock = 0;
			float price = 0.0f;
			for (auto &item : row.Fields)
			{
				if (item.Key == TEXT("ordertype"))
				{
					ordertype =	FCString::Atoi(*item.Value);
				}
				else if (item.Key == TEXT("userid"))
				{
					userid = FCString::Atoi(*item.Value);
				}
				else if (item.Key == TEXT("stock"))
				{
					stock = FCString::Atof(*item.Value);
				}
				else if (item.Key == TEXT("price"))
				{
					price = FCString::Atof(*item.Value);
				}
			}
			if (ordertype == 0)
			{
				AddSellOrderItem(price, stock);
			}
			else if (ordertype == 1)
			{
				AddBuyOrderItem(price,stock);
			}
		}
	}
}


