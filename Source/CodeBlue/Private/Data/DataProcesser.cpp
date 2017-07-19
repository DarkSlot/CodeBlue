// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "DataProcesser.h"

void UDataProcesser::BuyProduct(const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 stationid) {
	int32 RemainNum = num;

	FString order_sql = FString::Printf(
		TEXT("select orderid,num,price,userid from ProductOrder "
			"where `productid` =%d and `stationid`=%d and ordertype = 0 order by price"),
		productid, stationid);
	SQLiteResult result = SqliteLib->ExecuteQuery(order_sql);
	if (result.Success)
	{
		int32 orderrownum = result.Rows.Num();
		for (int32 i = 0; i < orderrownum; i++)
		{
			if (RemainNum<=0)
			{
				break;
			}
			TMap<FString, SQLiteField> &row = result.Rows[i].Fields;
			float orderprice = row["price"].RealValue;
			if (orderprice>price)
			{
				break;
			}
			int orderid = row["orderid"].IntValue;
			int ordernum = row["num"].IntValue;
			int sellerid = row["userid"].IntValue;
			if (ordernum>RemainNum)
			{
				int updated_order_num = ordernum - RemainNum;
				float dealed_money = orderprice * RemainNum;
				//cost money for the buyer
				if (!CostMoney(dealed_money,userid))
				{
					break;
				}

				//Remove the dealed stock
				UpdateOrderNum(orderid, updated_order_num);
				if (OnOrderListChanged.IsBound())
				{
					OnOrderListChanged.Broadcast(stationid, productid);
				}
				//add money for the seller
				AddMoney(dealed_money,sellerid);

				//add product to user's property
				AddProperty(productid, RemainNum, userid, stationid);
				RemainNum = 0;
			}
			else 
			{
				RemainNum = RemainNum - ordernum;
				float dealed_money = orderprice * ordernum;
				//cost money for the buyer
				if (!CostMoney(dealed_money, userid))
				{
					break;
				}
				//Remove the dealed stock
				RemoveOrder(orderid);
				if (OnOrderListChanged.IsBound())
				{
					OnOrderListChanged.Broadcast(stationid, productid);
				}
				//add money for the seller
				AddMoney(dealed_money, sellerid);
				//add product to user's property
				AddProperty(productid, ordernum, userid, stationid);
			}
		}
	}
	if (RemainNum > 0)
	{
		float dealed_money = price * RemainNum;
		if (CostMoney(dealed_money, userid))
		{
			AddOrder(1, productid, price, RemainNum, userid, stationid);
		}
	}
}

void UDataProcesser::SellProduct(const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 stationid) {
	if (!ReduceProperty(productid,num,userid,stationid))
	{
		return;
	}
	int32 RemainNum = num;
	FString product_sql = FString::Printf(
		TEXT("select `orderid`,`num`,`price`,`userid` from ProductOrder"
			" where `productid` =%d and `stationid`=%d and ordertype = 1 order by price desc"),
		productid, stationid);
	SQLiteResult result = SqliteLib->ExecuteQuery(product_sql);
	if (result.Success)
	{
		int32 orderownum = result.Rows.Num();
		for (int32 i = 0; i < orderownum; i++)
		{
			if (RemainNum <= 0)
			{
				break;
			}
			float orderprice = result.Rows[i].Fields["price"].RealValue;
			if (orderprice < price)
			{
				break;
			}
			TMap<FString, SQLiteField> &row = result.Rows[i].Fields;
			int orderid = row["orderid"].IntValue;
			int ordernum = row["num"].IntValue;
			int buyerid = row["userid"].IntValue;
			if (ordernum > RemainNum)
			{
				int updated_order_num = ordernum - RemainNum;
				float dealed_money = orderprice * RemainNum;
				//add property for the buyer
				AddProperty(productid, RemainNum, buyerid, stationid);
				//Remove the dealed stock
				UpdateOrderNum(orderid,updated_order_num);
				if (OnOrderListChanged.IsBound())
				{
					OnOrderListChanged.Broadcast(stationid, userid);
				}
				//add money for the seller
				AddMoney(dealed_money, userid);
				RemainNum = 0;
			}
			else
			{
				RemainNum = RemainNum - ordernum;
				float dealed_money = orderprice * ordernum;
				//add property for the buyer
				AddProperty(productid, ordernum, buyerid, stationid);
				//Remove the dealed stock
				RemoveOrder(orderid);
				if (OnOrderListChanged.IsBound())
				{
					OnOrderListChanged.Broadcast(stationid, productid);
				}
				//add money for the seller
				AddMoney(dealed_money, userid);
			}
		}
	}
	if (RemainNum > 0)
	{
		AddOrder(0, productid, price, RemainNum, userid, stationid);
	}
}

void UDataProcesser::AddOrder(const int32 ordertype, const int32 productid, const float price,
	const int32 num, const int32 userid, const int32 stationid) {
	FString publish_order_sql = FString::Printf(
		TEXT("insert into `ProductOrder`(`ordertype`,`productid`,`userid`,`stationid`,`num`,`price`,'updatetime')"
			" VALUES(%d, %d, %d,%d, %d, %f,datetime('now'));"), ordertype, productid, userid, stationid, num, price);
	SqliteLib->ExecuteNoQuery(publish_order_sql);

	if (OnOrderListChanged.IsBound())
	{
		OnOrderListChanged.Broadcast(stationid, productid);
	}
}

void UDataProcesser::RemoveOrder(const int32 orderid) {
	FString remove_sql = FString::Printf(
		TEXT("delete from `ProductOrder`  where orderid = %d"), orderid);
	SqliteLib->ExecuteNoQuery(remove_sql);
}

void UDataProcesser::UpdateOrderNum(const int32 orderid, const int32 num) {
	FString update_num_sql = FString::Printf(
		TEXT("update `ProductOrder` set `num` = %d,`updatetime`=datetime('now') where orderid = %d"), num, orderid);
	SqliteLib->ExecuteNoQuery(update_num_sql);
}

void UDataProcesser::UpdateOrderPrice(const int32 orderid, const float price) {
	FString update_price_sql = FString::Printf(
		TEXT("update `ProductOrder` set `price` = %f,`updatetime`=datetime('now') where orderid = %d"), price, orderid);
	SqliteLib->ExecuteNoQuery(update_price_sql);
	if (OnOrderListChanged.IsBound())
	{
		FString order_sql = FString::Printf(
			TEXT("select `productid`,`stationid` from ProductOrder"
				" where `orderid` =%d"),orderid);
		SQLiteResult result = SqliteLib->ExecuteQuery(order_sql);
		if (result.Success&&result.Rows.Num()>0)
		{
			TMap<FString, SQLiteField> &row = result.Rows[0].Fields;
			OnOrderListChanged.Broadcast(row["stationid"].IntValue, row["productid"].IntValue);
		}
	}
}
bool UDataProcesser::AddProperty(const int32 productid, const int32 num,
	const int32 userid, const int32 stationid) {
	FString update_property_sql = FString::Printf(TEXT("update Property set `num` = `num` + %d"
		" where `userid` = %d and `stationid` = %d and `productid` = %d"
		), num, userid, stationid, productid);
	int32 affected = SqliteLib->ExecuteNoQuery(update_property_sql);
	if (affected == 0)
	{
		FString add_property_sql = FString::Printf(TEXT("insert into Property"
			"(`userid`,`stationid`,`productid`,`num`) values(%d,%d,%d,%d)"
		), userid, stationid, productid, num);
		affected = SqliteLib->ExecuteNoQuery(add_property_sql);
	}
	return (affected ==1);
}

bool UDataProcesser::ReduceProperty(const int32 productid, const int32 num,
	const int32 userid, const int32 stationid) {
	FString update_property_sql = FString::Printf(TEXT("update Property set `num` = `num` - %d"
		" where `userid` = %d and `stationid` = %d and `productid` = %d and `num`>= %d"
	), num, userid, stationid, productid, num);
	int32 affected = SqliteLib->ExecuteNoQuery(update_property_sql);
	return (affected == 1);
}

bool UDataProcesser::AddMoney(const float num, const int32 userid) {
	if (num<0.0f)
	{
		return false;
	}
	FUserDataItem *useritem = UserData.Find(userid);
	if (useritem)
	{
		useritem->money += num;
		return true;
	}
	return false;
}
bool UDataProcesser::CostMoney(const float num, const int32 userid) {
	if (num<0.0f)
	{
		return false;
	}
	FUserDataItem *useritem = UserData.Find(userid);
	if (useritem)
	{
		if (useritem->money<num)
		{
			return false;
		}
		useritem->money -= num;
		return true;
	}
	return false;
}
float UDataProcesser::CheckMoney(const int32 userid) {
	FUserDataItem *useritem = UserData.Find(userid);
	if (useritem)
	{
		return useritem->money;
	}
	return 0.0f;
}

int32 UDataProcesser::CheckProductStock(const int32 productid,
	const int32 userid, const int32 stationid) {
	FString property_sql = FString::Printf(
		TEXT("select `num` from Property"
			" where `userid` =%d and `stationid`=%d and `productid`=%d"), userid,
		stationid, productid);
	SQLiteResult result = SqliteLib->ExecuteQuery(property_sql);
	if (result.Success&&result.Rows.Num()>0)
	{
		return result.Rows[0].Fields["num"].IntValue;
	}
	return 0;
}
UTexture2D *UDataProcesser::GetProductIcon(const int32 productid) {
	FProductInfoItem **info = ProductInfo.Find(productid);
	if (info)
	{
		FString path = (*info)->iconlink;
		UTexture2D* texture = LoadObject<UTexture2D>(nullptr, *path);
		if (texture) return texture;
	}
	return nullptr;
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
	//user info
	UDataTable *UserInfoDataTable = 
		LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/UserData.UserData"));
	TArray<FUserDataItem *> UserInfoArray;
	UserInfoDataTable->GetAllRows(ContextString, UserInfoArray);
	for (auto row : UserInfoArray)
	{
		UserData.Add(row->userid, FUserDataItem(*row));
	}
	//station info
	UDataTable *StationInfoDataTable =
		LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/StationData.StationData"));
	TArray<FStationInfoDataItem *> StationInfoArray;
	StationInfoDataTable->GetAllRows(ContextString, StationInfoArray);
	for (auto row : StationInfoArray)
	{
		StationData.Add(row->UserId, new FStationInfoDataItem(*row));
	}
	SqliteLib = NewObject<USQLiteLibrary>(this);
	SqliteLib->NewDatabase();
	//property table
	FString create_property_sql = TEXT("CREATE TABLE `Property` ( "
		" `userid` INTEGER NOT NULL, `stationid` INTEGER NOT NULL, `productid` INTEGER NOT NULL,"
		" `num` INTEGER NOT NULL DEFAULT 0,"
		" PRIMARY KEY(`userid`,`stationid`,`productid`))");
	SqliteLib->ExecuteNoQuery(create_property_sql);
	//order table
	FString create_order_sql = TEXT("CREATE TABLE `ProductOrder` ( "
		"`orderid` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
		"`ordertype` INTEGER NOT NULL, `productid` INTEGER NOT NULL, "
		"`userid` INTEGER NOT NULL, `stationid` INTEGER NOT NULL DEFAULT 0, "
		"`num` INTEGER NOT NULL, `price` Real NOT NULL, `updatetime` TEXT NOT NULL )");
	SqliteLib->ExecuteNoQuery(create_order_sql);
	FString create_index0_sql = TEXT("CREATE INDEX `orderindex0` ON "
		"`ProductOrder` (`productid` ,`stationid` )");
	SqliteLib->ExecuteNoQuery(create_index0_sql);
	FString create_index1_sql = TEXT("CREATE INDEX `orderindex1` ON "
		"`ProductOrder` (`productid` ,`stationid`, 'userid')");
	SqliteLib->ExecuteNoQuery(create_index1_sql);
}

bool UDataProcesser::GetProductOrder(const int32 productid, const int32 stationid, OrderList &list) {
	FString query_sql = FString::Printf(TEXT("select * from `ProductOrder`"
		" where productid = %d and stationid = %d"), productid, stationid);
	SQLiteResult result = SqliteLib->ExecuteQuery(query_sql);
	if (result.Success)
	{
		int32 numrow = result.Rows.Num();
		for (int32 i = 0; i < numrow; i++)
		{
			TMap<FString, SQLiteField> &row = result.Rows[i].Fields;
			int32 orderid = row["orderid"].IntValue;
			int32 ordertype = row["ordertype"].IntValue;
			int32 pid = row["productid"].IntValue;
			int32 userid = row["userid"].IntValue;
			int32 sid = row["stationid"].IntValue;
			int32 num = row["num"].IntValue;
			float price = row["price"].RealValue;
			FString updatetime = row["updatetime"].StringValue;
			list.Add(FOrderDataItem(ordertype, pid,userid, sid,num,price, updatetime));
		}
		return true;
	}
	return false;
}
bool UDataProcesser::GetProductOrderByPrice(const int32 productid,
	const int32 stationid, bool isHighest, FOrderDataItem &item) {
	FString priceorder = isHighest ? TEXT("desc ") : TEXT("");
	int32 ordertype = isHighest ? 1 : 0;
	FString query_sql = FString::Printf(TEXT("select `stationid` from `ProductOrder`"
		" where `productid` = %d and `stationid`=%d and `ordertype`=%d order by `price` %slimit 1"),
		productid, stationid, ordertype,*priceorder);
	SQLiteResult result = SqliteLib->ExecuteQuery(query_sql);
	if (result.Success&&result.Rows.Num()>0)
	{
		TMap<FString, SQLiteField> &row = result.Rows[0].Fields;
		item.orderid = row["orderid"].IntValue;
		item.ordertype = row["ordertype"].IntValue;
		item.productid = row["productid"].IntValue;
		item.userid = row["userid"].IntValue;
		item.stationid = row["stationid"].IntValue;
		item.num = row["num"].IntValue;
		item.price = row["price"].RealValue;
		return true;
	}
	return false;
}
int32 UDataProcesser::GetSuitableStationByPrice(const int32 productid, bool isHighest, float &price) {
	FString priceorder = isHighest ? TEXT("desc ") : TEXT("");
	int32 ordertype = isHighest ? 1 : 0;
	FString query_sql = FString::Printf(TEXT("select `stationid`,`price` from `ProductOrder`"
		" where `productid` = %d and `ordertype`=%d order by `price` %slimit 1"),
		productid, ordertype, *priceorder);
	SQLiteResult result = SqliteLib->ExecuteQuery(query_sql);
	if (result.Success&&result.Rows.Num()>0)
	{
		price = result.Rows[0].Fields["price"].RealValue;
		return result.Rows[0].Fields["stationid"].IntValue;
	}
	return -1;
}
int32 UDataProcesser::CountOrderNum(const int32 productid, const int32 userid,
	const int32 stationid) {
	FString query_sql = FString::Printf(TEXT("select sum(num) as total from `ProductOrder`"
		" where productid = %d and userid = %d and stationid = %d"),
		productid, userid, stationid);
	SQLiteResult result = SqliteLib->ExecuteQuery(query_sql);
	if (result.Success&&result.Rows.Num()>0)
	{
		SQLiteField &field = result.Rows[0].Fields["total"];
		if (field.Type== SQLiteResultValueTypes::Integer)
		{
			return result.Rows[0].Fields["total"].IntValue;
		}
	}
	return 0;
}	
int32 UDataProcesser::ChangeOrderPriceByUserStation(const int32 productid,
	const int32 userid,	const int32 stationid, const float price) {
	float delta_money = 0.0f;
	FString delta_price_sql = FString::Printf(TEXT("select sum((%f-`price`)*`num`) as deltaprice from `ProductOrder`"
		"where productid = %d and userid = %d and stationid = %d"), 
		price, productid, userid, stationid);
	SQLiteResult queryresult = SqliteLib->ExecuteQuery(delta_price_sql);
	if (queryresult.Success&&queryresult.Rows.Num()>0)
	{
		SQLiteField &field = queryresult.Rows[0].Fields["deltaprice"];
		if (field.Type == SQLiteResultValueTypes::Float)
		{
			delta_money = field.RealValue;
			bool canupdateprice = false;
			if (delta_money>0.0f)
			{
				if (CostMoney(delta_money, userid))
				{
					canupdateprice = true;
				}
			}
			else
			{
				AddMoney(-delta_money,userid);
				canupdateprice = true;
			}
			if (canupdateprice)
			{
				FString update_sql = FString::Printf(TEXT("update `ProductOrder`"
					" set `price` = %f,`updatetime`=datetime('now') where productid = %d and userid = %d and stationid = %d"),
					price, productid, userid, stationid);
				int32 result = SqliteLib->ExecuteNoQuery(update_sql);

				if (OnOrderListChanged.IsBound())
				{
					OnOrderListChanged.Broadcast(stationid, productid);
				}
				return result;
			}
		}
	}
	return 0;
}
UserList &UDataProcesser::GetUserData() {
	return UserData;
}
TMap<int32, FProductInfoItem *> &UDataProcesser::GetProductInfo() {
	return ProductInfo;
}
StationInfoList &UDataProcesser::GetStationData() {
	return StationData;
}
FString UDataProcesser::GetProductName(const int32 productid) {
	FProductInfoItem **info = ProductInfo.Find(productid);
	if (info)
	{
		return (*info)->productname;
	}
	return TEXT("");
}

int32 UDataProcesser::CreateNewUser(FUserDataItem &item) {
	int32 i = 10000;
	while (true)
	{
		if (UserData.Contains(i))
		{
			i++;
			continue;
		}
		else
		{
			break;
		}
	}
	item.userid = i;
	UserData.Add(i, item);
	return i;
}

//void UDataProcesser::RemoveOrder(FOrderDataItem *order) {
//	OnOrderListChanged.Broadcast(order->stationid, order->productid);
//
//	ProductOrderList *stationOrderlist = OrderData.Find(order->stationid);
//	OrderList *orderlist = stationOrderlist->Find(order->productid);
//	orderlist->Remove(order);
//	TArray<OrderRemoveEvent> *listeners = OrderRemoveListeners.Find(order);
//	if (listeners)
//	{
//		for (auto listener : *listeners)
//		{
//			listener(order);
//		}
//		OrderRemoveListeners.Remove(order);
//	}
//	delete order;
//}