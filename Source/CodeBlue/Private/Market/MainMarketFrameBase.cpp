// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MainMarketFrameBase.h"
#include "../Localization/ProductLocalizationList.h"
//#include "SQLiteDatabase.h"
#include "../GMGameInstance.h"
#include "../Data/DataProcesser.h"

void UMainMarketFrameBase::UpdateList() {
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(UGameplayStatics::GetGameInstance(this));
	TMap<int32, FProductInfoItem *> &InfoMap = GameInstance->DataProcesser->GetProductInfo();
	for (auto info: InfoMap)
	{
		AddProductMenuItem(ProductLocalizationList::FindProductName(info.Value->productname), info.Key);
	}
}
void UMainMarketFrameBase::UpdateOrderList(const int32 product, const int32 station) {
	CurrentProductId = product;
	ClearOrderList();
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(UGameplayStatics::GetGameInstance(this));
	OrderList orderlist;
	GameInstance->DataProcesser->GetProductOrder(product, station,orderlist);
	if (orderlist.Num()>0)
	{
		for (auto &order : orderlist)
		{
			if (order.ordertype == 0)
			{
				AddSellOrderItem(order.price, order.num, order.updatetime);
			}
			else
			{
				AddBuyOrderItem(order.price, order.num, order.updatetime);
			}
		}
	}
}


