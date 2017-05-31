// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MainMarketFrameBase.h"
#include "../Localization/ProductLocalizationList.h"
//#include "SQLiteDatabase.h"
#include "../GMGameInstance.h"
#include "../Data/DataProcesser.h"

void UMainMarketFrameBase::UpdateList(FName MarketName) {
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(UGameplayStatics::GetGameInstance(this));
	TMap<int32, FProductDataTable *> &InfoMap = GameInstance->DataProcesser->GetProductInfo();
	for (auto info: InfoMap)
	{
		AddProductMenuItem(ProductLocalizationList::FindProductName(info.Value->productname), info.Key);
	}
}
void UMainMarketFrameBase::UpdateOrderList(const int32 product, const int32 station) {
	CurrentProductId = product;
	ClearOrderList();
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(UGameplayStatics::GetGameInstance(this));
	OrderList *orderlist;
	GameInstance->DataProcesser->GetProductOrder(product, station,&orderlist);
	if (orderlist)
	{
		for (auto order : *orderlist)
		{
			if (order->ordertype == 0)
			{
				AddSellOrderItem(order->price, order->stock);
			}
			else
			{
				AddBuyOrderItem(order->price, order->stock);
			}
		}
	}
	//FString product_sql = TEXT("select * from ProductOrder where productid =");
	//product_sql.AppendInt(product);
	//FSQLiteQueryResult result = USQLiteDatabase::GetData(TEXT("market"), product_sql);
	//if (result.Success)
	//{
	//	for (auto &row : result.ResultRows)
	//	{
	//		int32 ordertype = 0;
	//		int32 userid = 0;
	//		int32 stock = 0;
	//		float price = 0.0f;
	//		for (auto &item : row.Fields)
	//		{
	//			if (item.Key == TEXT("ordertype"))
	//			{
	//				ordertype =	FCString::Atoi(*item.Value);
	//			}
	//			else if (item.Key == TEXT("userid"))
	//			{
	//				userid = FCString::Atoi(*item.Value);
	//			}
	//			else if (item.Key == TEXT("stock"))
	//			{
	//				stock = FCString::Atof(*item.Value);
	//			}
	//			else if (item.Key == TEXT("price"))
	//			{
	//				price = FCString::Atof(*item.Value);
	//			}
	//		}
	//		if (ordertype == 0)
	//		{
	//			AddSellOrderItem(price, stock);
	//		}
	//		else if (ordertype == 1)
	//		{
	//			AddBuyOrderItem(price,stock);
	//		}
	//	}
	//}
}


