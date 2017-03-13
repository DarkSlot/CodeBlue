// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "SellProductCommand.h"
#include "SQLiteDatabase.h"

SellProductCommand::SellProductCommand(const int32 productid, const float price, const int32 num,
	const int32 userid, const int32 depotid) :
	ProductId(productid),
	Price(price),
	Num(num),
	UserId(userid),
	DepotId(depotid)
{
}

SellProductCommand::~SellProductCommand()
{
}
void SellProductCommand::Execute() {
	FString query_property_sql = FString::Printf(
		TEXT("select propertyid,num from Property"
			"where userid =%d and depotid = %d and productid = %d"), UserId, DepotId, ProductId);
	SQLiteResult property_result = USQLiteDatabase::ExecuteQuery(TEXT("market"), query_property_sql);
	if (!property_result.Success|| property_result.Rows.Num()==0)
	{
		UE_LOG(CodeBlueLog, Verbose, TEXT("Not Enough Product"));
		return;
	}
	else
	{
		if (property_result.Rows[0].Fields["num"].IntValue <Num)
		{
			UE_LOG(CodeBlueLog, Verbose, TEXT("Not Enough Product"));
			return;
		}		
		FString removeproperty_sql = FString::Printf(
			TEXT("update Property set num = num -%d where propertyid=%d"), Num, property_result.Rows[0].Fields["propertyid"].IntValue);
		USQLiteDatabase::ExecuteNoQuery(TEXT("market"), removeproperty_sql);
	}

	FString product_sql = FString::Printf(
		TEXT("select orderid,stock,price,userid from ProductOrder"
			"where productid =%d and ordertype = 1 order by price"), ProductId);
	SQLiteResult result = USQLiteDatabase::ExecuteQuery(TEXT("market"), product_sql);
	if (result.Success)
	{
		int32 ordernum = result.Rows.Num();
		int32 RemainNum = Num;
		for (int32 i = 0; i < ordernum; i++)
		{
			if (RemainNum <= 0)
			{
				break;
			}
			float orderprice = result.Rows[i].Fields["price"].RealValue;
			if (orderprice<Price)
			{
				break;
			}
			int orderid = result.Rows[i].Fields["orderid"].IntValue;
			int ordernum = result.Rows[i].Fields["stock"].IntValue;
			int sellerid = result.Rows[i].Fields["userid"].IntValue;
			if (ordernum >= RemainNum)
			{
				int updated_order_num = ordernum - RemainNum;
				float avg_price = (orderprice + Price)*0.5f;
				float dealed_money = avg_price * RemainNum;
				//Remove the dealed stock
				if (ordernum == RemainNum)
				{
					FString update_num_sql = FString::Printf(
						TEXT("delete from ProductOrder  where orderid = %d"), orderid);
					USQLiteDatabase::ExecuteNoQuery(TEXT("market"), update_num_sql);
				}
				else
				{
					FString update_num_sql = FString::Printf(
						TEXT("update ProductOrder set stock = %d where orderid = %d"), updated_order_num, orderid);
					USQLiteDatabase::ExecuteNoQuery(TEXT("market"), update_num_sql);
				}
				//cost money for the buyer
				FString addmoney_sql = FString::Printf(
					TEXT("update User set money = money - %f where userid = %d"), dealed_money, sellerid);
				USQLiteDatabase::ExecuteNoQuery(TEXT("market"), addmoney_sql);
				//add money for the seller
				FString costmoney_sql = FString::Printf(
					TEXT("update User set money = money + %f where userid = %d"), dealed_money, UserId);
				USQLiteDatabase::ExecuteNoQuery(TEXT("market"), costmoney_sql);
				RemainNum = 0;
			}
			else
			{
				RemainNum = RemainNum - ordernum;
				float avg_price = (orderprice + Price)*0.5f;
				float dealed_money = avg_price * ordernum;

				//Remove the dealed stock
				FString update_num_sql = FString::Printf(
					TEXT("delete from ProductOrder  where orderid = %d"), orderid);
				USQLiteDatabase::ExecuteNoQuery(TEXT("market"), update_num_sql);
				//cost money for the buyer
				FString addmoney_sql = FString::Printf(
					TEXT("update User set money = money - %f where userid = %d"), dealed_money, sellerid);
				USQLiteDatabase::ExecuteNoQuery(TEXT("market"), addmoney_sql);
				//add money for the seller
				FString costmoney_sql = FString::Printf(
					TEXT("update User set money = money + %f where userid = %d"), dealed_money, UserId);
				USQLiteDatabase::ExecuteNoQuery(TEXT("market"), costmoney_sql);
			}
		}
		if (RemainNum > 0)
		{
			FString publish_order_sql = FString::Printf(
				TEXT("insert into `ProductOrder`(`ordertype`,`productid`,`userid`,`stock`,`price`) VALUES(0, %d, %d, %d, %f);"), ProductId, UserId, RemainNum, Price);
			USQLiteDatabase::ExecuteNoQuery(TEXT("market"), publish_order_sql);
		}
	}

}
