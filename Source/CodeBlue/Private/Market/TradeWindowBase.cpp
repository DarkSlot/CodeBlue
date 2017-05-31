// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "TradeWindowBase.h"
#include "../Localization/ProductLocalizationList.h"
//#include "SQLiteDatabase.h"
#include "../GMGameInstance.h"
#include "../Data/DataProcesser.h"


void UTradeWindowBase::UpdateTradeWindow(const int32 productid, const int32 stationid, const bool IsBuyWindow) {
	bIsBuyWindow = IsBuyWindow;
	ProductId = productid;
	int32 ordertype = IsBuyWindow ? 0 : 1;
	auto CompareFun = [ordertype](float a, float b) {return (ordertype ==0)?(a < b):(a>b); };

	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(UGameplayStatics::GetGameInstance(this));
	OrderList *orderlist = nullptr;
	GameInstance->DataProcesser->GetProductOrder(productid, stationid, &orderlist);
	FOrderDataItem *MatchItem = nullptr;
	if (orderlist)
	{
		for (auto order : *orderlist)
		{
			if (order->ordertype == ordertype)
			{
				if (!MatchItem)
				{
					MatchItem = order;
				}
				else if (CompareFun(order->price, MatchItem->price))
				{
					MatchItem = order;
				}
			}
		}
	}
	if (MatchItem)
	{
		InitTradeWindow(ProductLocalizationList::FindProductName(
			GameInstance->DataProcesser->GetProductName(MatchItem->productid)),
			MatchItem->price);
	}
}


