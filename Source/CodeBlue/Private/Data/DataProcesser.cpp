// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "DataProcesser.h"

void UDataProcesser::BuyProduct(const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 stationid) {
	FUserDataItem *buyeritem = UserData.Find(userid);

	TArray<FOrderDataItem *> RegroupedOrderList;

	ProductOrderList *stationOrderlist = OrderData.Find(stationid);
	OrderList *orderlist = nullptr;
	if (stationOrderlist)
	{
		orderlist = stationOrderlist->Find(productid);
		for (auto &order : *orderlist)
		{
			if (order->ordertype == 0)
			{
				RegroupedOrderList.Add(order);
			}
		}
		RegroupedOrderList.Sort([](const FOrderDataItem& A, const FOrderDataItem& B) {
			return A.price < B.price;
		});
	}
	int32 allordernum = RegroupedOrderList.Num();
	int32 RemainNum = num;
	for (int32 i = 0; i < allordernum; i++)
	{
		if (RemainNum <= 0)
		{
			break;
		}
		FOrderDataItem *orderitem = RegroupedOrderList[i];
		FUserDataItem *selleritem = &(UserData[orderitem->userid]);
		float orderprice = orderitem->price;
		if (orderprice>price)
		{
			break;
		}
		bool unsavedorder = orderitem->unsaved;
		int orderid = orderitem->orderid;
		int ordernum = orderitem->stock;
		int sellerid = orderitem->userid;
		if (ordernum >= RemainNum)
		{
			int updated_order_num = ordernum - RemainNum;
			float avg_price = (orderprice + price)*0.5f;
			float dealed_money = avg_price * RemainNum;
			if (buyeritem->money<dealed_money)
			{
				break;
			}
			//Remove the dealed stock
			if (ordernum == RemainNum)
			{
				if (unsavedorder)
				{
					RemoveOrder(orderitem);
				}
				else
				{
					RemovedOrderList.Add(orderid);
					RemoveOrder(orderitem);
				}
			}
			else
			{
				orderitem->stock = updated_order_num;
			}
			//add money for the seller
			selleritem->money += dealed_money;
			//cost money for the buyer
			buyeritem->money -= dealed_money;

			//add product to user's property
			StationPropertyList *stationlist = PropertyData.Find(sellerid);
			if (!stationlist)
			{
				stationlist = &(PropertyData.Add(sellerid));
			}
			PropertyList *propertylist = stationlist->Find(stationid);
			if (!propertylist)
			{
				propertylist = &(stationlist->Add(stationid));
			}
			FPropertyDataItem *propertyitem = propertylist->Find(productid);
			if (!propertyitem)
			{
				propertyitem = &(propertylist->Add(productid));
			}
			propertyitem->num += RemainNum;
			RemainNum = 0;
		}
		else
		{
			RemainNum = RemainNum - ordernum;
			float avg_price = (orderprice + price)*0.5f;
			float dealed_money = avg_price * ordernum;

			//Remove the dealed stock
			if (unsavedorder)
			{
				RemoveOrder(orderitem);
			}
			else
			{
				RemovedOrderList.Add(orderid);
				RemoveOrder(orderitem);
			}
			//add money for the seller
			selleritem->money += dealed_money;
			//cost money for the buyer
			buyeritem->money -= dealed_money;

			//add product to user's property
			//add product to user's property
			StationPropertyList *stationlist = PropertyData.Find(sellerid);
			if (!stationlist)
			{
				stationlist = &(PropertyData.Add(sellerid));
			}
			PropertyList *propertylist = stationlist->Find(stationid);
			if (!propertylist)
			{
				propertylist = &(stationlist->Add(stationid));
			}
			FPropertyDataItem *propertyitem = propertylist->Find(productid);
			if (!propertyitem)
			{
				propertyitem = &(propertylist->Add(productid));
			}
			propertyitem->num += RemainNum;
		}
	}
	if (RemainNum > 0)
	{
		//add order
		if (!stationOrderlist)
		{
			stationOrderlist = &(OrderData.Add(stationid));
		}
		if (!orderlist)
		{
			orderlist = &(stationOrderlist->Add(productid));
		}
		orderlist->Add(new FOrderDataItem(1,productid, userid, stationid, RemainNum, price));

		OnOrderListChanged.Broadcast(stationid, productid);
	}
}

void UDataProcesser::SellProduct(const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 stationid) {
	FUserDataItem *selleritem = UserData.Find(userid);

	TArray<FOrderDataItem *> RegroupedOrderList;
	OrderList *orderlist = nullptr;
	ProductOrderList *stationOrderlist = OrderData.Find(stationid);
	if (stationOrderlist)
	{
		orderlist = stationOrderlist->Find(productid);

		for (auto &order : *orderlist)
		{
			if (order->ordertype == 1)
			{
				RegroupedOrderList.Add(order);
			}
		}
		RegroupedOrderList.Sort([](const FOrderDataItem& A, const FOrderDataItem& B) {
			return A.price > B.price;
		});
	}
	int32 allordernum = RegroupedOrderList.Num();
	int32 RemainNum = num;
	for (int32 i = 0; i < allordernum; i++)
	{
		if (RemainNum <= 0)
		{
			break;
		}
		FOrderDataItem *orderitem = RegroupedOrderList[i];
		FUserDataItem *buyeritem = &(UserData[orderitem->userid]);
		float orderprice = orderitem->price;
		if (orderprice<price)
		{
			break;
		}
		bool unsavedorder = orderitem->unsaved;
		int orderid = orderitem->orderid;
		int ordernum = orderitem->stock;
		int buyerid = orderitem->userid;
		if (ordernum >= RemainNum)
		{
			int updated_order_num = ordernum - RemainNum;
			float avg_price = (orderprice + price)*0.5f;
			float dealed_money = avg_price * RemainNum;
			if (buyeritem->money<dealed_money)
			{
				break;
			}
			//Remove the dealed stock
			if (ordernum == RemainNum)
			{
				if (unsavedorder)
				{
					RemoveOrder(orderitem);
				}
				else
				{
					RemovedOrderList.Add(orderid);
					RemoveOrder(orderitem);
				}
			}
			else
			{
				orderitem->stock = updated_order_num;
			}
			//add money for the seller
			selleritem->money -= dealed_money;
			//cost money for the buyer
			buyeritem->money -= dealed_money;

			//add product to user's property
			StationPropertyList *stationlist = PropertyData.Find(buyerid);
			if (!stationlist)
			{
				stationlist = &(PropertyData.Add(buyerid));
			}
			PropertyList *propertylist = stationlist->Find(stationid);
			if (!propertylist)
			{
				propertylist = &(stationlist->Add(stationid));
			}
			FPropertyDataItem *propertyitem = propertylist->Find(productid);
			if (!propertyitem)
			{
				propertyitem = &(propertylist->Add(productid));
			}
			propertyitem->num += RemainNum;
			RemainNum = 0;
		}
		else
		{
			RemainNum = RemainNum - ordernum;
			float avg_price = (orderprice + price)*0.5f;
			float dealed_money = avg_price * ordernum;

			//Remove the dealed stock
			if (unsavedorder)
			{
				RemoveOrder(orderitem);
			}
			else
			{
				RemovedOrderList.Add(orderid);
				RemoveOrder(orderitem);
			}
			//add money for the seller
			selleritem->money += dealed_money;
			//cost money for the buyer
			buyeritem->money -= dealed_money;

			//add product to user's property
			//add product to user's property
			StationPropertyList *stationlist = PropertyData.Find(buyerid);
			if (!stationlist)
			{
				stationlist = &(PropertyData.Add(buyerid));
			}
			PropertyList *propertylist = stationlist->Find(stationid);
			if (!propertylist)
			{
				propertylist = &(stationlist->Add(stationid));
			}
			FPropertyDataItem *propertyitem = propertylist->Find(productid);
			if (!propertyitem)
			{
				propertyitem = &(propertylist->Add(productid));
			}
			propertyitem->num += RemainNum;
		}
	}
	if (RemainNum > 0)
	{
		if (!stationOrderlist)
		{
			stationOrderlist = &(OrderData.Add(stationid));
		}
		if (!orderlist)
		{
			orderlist = &(stationOrderlist->Add(productid));
		}
		orderlist->Add(new FOrderDataItem(0, productid, userid, stationid, RemainNum, price));
		OnOrderListChanged.Broadcast(stationid, productid);

		//remove stock
		StationPropertyList *stationlist = PropertyData.Find(userid);
		if (!stationlist)
		{
			stationlist = &(PropertyData.Add(userid));
		}
		PropertyList *propertylist = stationlist->Find(stationid);
		if (!propertylist)
		{
			propertylist = &(stationlist->Add(stationid));
		}
		FPropertyDataItem *propertyitem = propertylist->Find(productid);
		if (!propertyitem)
		{
			propertyitem = &(propertylist->Add(productid));
		}
		propertyitem->num -= RemainNum;
	}
}


bool UDataProcesser::ProduceProduct(const int32 productid, const int32 num,
	const int32 userid, const int32 stationid) {
	//add product to user's property
	StationPropertyList *stationlist = PropertyData.Find(userid);
	if (!stationlist)
	{
		stationlist = &(PropertyData.Add(userid));
	}
	PropertyList *propertylist = stationlist->Find(stationid);
	if (!propertylist)
	{
		propertylist = &(stationlist->Add(stationid));
	}
	FPropertyDataItem *propertyitem = propertylist->Find(productid);
	if (!propertyitem)
	{
		propertyitem = &(propertylist->Add(productid));
	}
	propertyitem->num += num;
	return true;
}
bool UDataProcesser::CostProduct(const int32 productid, const int32 num,
	const int32 userid, const int32 stationid) {
	//add product to user's property
	StationPropertyList *stationlist = PropertyData.Find(userid);
	if (!stationlist)
	{
		return false;
	}
	PropertyList *propertylist = stationlist->Find(stationid);
	if (!propertylist)
	{
		return false;
	}
	FPropertyDataItem *propertyitem = propertylist->Find(productid);
	if (!propertyitem)
	{
		return false;
	}
	propertyitem->num -= num;
	return true;
}

int32 UDataProcesser::CheckProductStock(const int32 productid,
	const int32 userid, const int32 stationid) {
	StationPropertyList *stationlist = PropertyData.Find(userid);
	if (!stationlist)
	{
		return 0;
	}
	PropertyList *propertylist = stationlist->Find(stationid);
	if (!propertylist)
	{
		return 0;
	}
	FPropertyDataItem *propertyitem = propertylist->Find(productid);
	if (!propertyitem)
	{
		return 0;
	}
	return propertyitem->num;
}
//FOnOrderListChanged &UDataProcesser::GetOrderListChangeEvent(
//	const int32 stationid, const int32 productid) {
//	OrderEventList &eventlist = OrderEventData.FindOrAdd(stationid);
//	FOnOrderListChanged &orderlistevent = eventlist.FindOrAdd(productid);
//	return orderlistevent;
//}
void UDataProcesser::Init() {
	//product info
	UDataTable *ProductInfoDataTable = 
		LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/ProductData.ProductData"));

	static const FString ContextString(TEXT("GENERAL"));

	TArray<FProductInfoItem *> ProductArray;
	ProductInfoDataTable->GetAllRows(ContextString, ProductArray);
	for (auto row : ProductArray)
	{
		ProductInfo.Add(row->productid, new FProductInfoItem(*row));
	}
	//station trade info
	UDataTable *StationInfoDataTable = 
		LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/StationTradeList.StationTradeList"));
	TArray<FStationTradeDataItem *> StationInfoArray;
	StationInfoDataTable->GetAllRows(ContextString, StationInfoArray);
	for (auto row : StationInfoArray)
	{
		StationTradeInfo.Add(row->userid, new FStationTradeDataItem(*row));
	}
}

bool UDataProcesser::GetProductOrder(const int32 productid,
	const int32 stationid, OrderList **list) {
	ProductOrderList *stationOrderlist = OrderData.Find(stationid);
	if (stationOrderlist)
	{
		OrderList *orderlist = stationOrderlist->Find(productid);
		*list = orderlist;
		return true;
	}
	*list = nullptr;
	return false;
}
TMap<int32, FProductInfoItem *> &UDataProcesser::GetProductInfo() {
	return ProductInfo;
}
StationTradeList &UDataProcesser::GetStationTradeInfo() {
	return StationTradeInfo;
}
FString UDataProcesser::GetProductName(const int32 productid) {
	FProductInfoItem **info = ProductInfo.Find(productid);
	if (info)
	{
		return (*info)->productname;
	}
	return TEXT("");
}


void UDataProcesser::RemoveOrder(FOrderDataItem *order) {
	OnOrderListChanged.Broadcast(order->stationid, order->productid);

	ProductOrderList *stationOrderlist = OrderData.Find(order->stationid);
	OrderList *orderlist = stationOrderlist->Find(order->productid);
	orderlist->Remove(order);
	TArray<OrderRemoveEvent> *listeners = OrderRemoveListeners.Find(order);
	if (listeners)
	{
		for (auto listener : *listeners)
		{
			listener(order);
		}
		OrderRemoveListeners.Remove(order);
	}
	delete order;
}