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
	StationId = stationid;
	int32 ordertype = IsBuyWindow ? 0 : 1;
	auto CompareFun = [ordertype](float a, float b) {return (ordertype ==0)?(a < b):(a>b); };

	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(UGameplayStatics::GetGameInstance(this));
	//OrderList orderlist;
	FOrderDataItem item;
	if (GameInstance->DataProcesser->GetProductOrderByPrice(productid, stationid, !IsBuyWindow, item)) {
		InitTradeWindow(ProductLocalizationList::FindProductName(
			GameInstance->DataProcesser->GetProductName(productid)),
			item.price);
	}
	else
	{
		FProductInfoItem *infoitem = GameInstance->DataProcesser->GetProductInfo()[productid];
		InitTradeWindow(ProductLocalizationList::FindProductName(
			infoitem->productname),
			infoitem->baseprice);
	}
}


