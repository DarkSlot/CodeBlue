// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "TradeWindowBase.h"
#include "../Localization/ProductLocalizationList.h"
#include "SQLiteDatabase.h"


void UTradeWindowBase::UpdateTradeWindow(const int32 productid, const bool IsBuyWindow) {
	ProductId = productid;
	int32 ordertype = IsBuyWindow ? 1 : 0;
	FString product_sql = FString::Printf(
		TEXT("select s1.stock,s1.price,s2.productname from ProductOrder"
		" as s1 join Product as s2 on s1.productid = s2.productid where s1.productid =%d"
		" and s1.ordertype = %d "), ProductId, ordertype);
	SQLiteResult result = USQLiteDatabase::ExecuteQuery(TEXT("market"), product_sql);
	if (result.Success)
	{
		if (result.Rows.Num())
		{
			FString productname = result.Rows[0].Fields["productname"].ToString();
			InitTradeWindow(ProductLocalizationList::FindProductName(productname),
				result.Rows[0].Fields["price"].RealValue);
		}
	}
}


