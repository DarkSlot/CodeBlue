// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "OrderDataItem.generated.h"

class UDataProcesser;
/**
 * 
 */
USTRUCT(Blueprintable)
struct FOrderDataItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	bool unsaved;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 orderid;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 ordertype;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 productid;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 userid;
	
	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 stationid;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	int32 num;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	float price;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	FString updatetime;

	FOrderDataItem()
		:unsaved(true),
		orderid(0),
		ordertype(0),
		productid(0),
		userid(0),
		stationid(0),
		num(0),
		price(0.0f) {}

	FOrderDataItem(int32 oid,int32 type, int32 product, int32 user, int32 station, int32 stocknum, float tradeprice,FString time)
		:unsaved(true),
		orderid(oid),
		ordertype(type),
		productid(product),
		userid(user),
		stationid(station),
		num(stocknum),
		price(tradeprice),
		updatetime(time){}
};
typedef TArray<FOrderDataItem> OrderList;
//key is productid
typedef TMap<int32, OrderList> ProductOrderList;
//key is stationid
typedef TMap<int32, ProductOrderList> StationOrderList;

typedef TFunction<void(FOrderDataItem *)> OrderRemoveEvent;
typedef TMap<FOrderDataItem *, TArray<OrderRemoveEvent>> OrderRemoveEventList;
////key is productid
//typedef TMap<int32, FOnOrderListChanged> OrderEventList;
////key is stationid
//typedef TMap<int32, OrderEventList> StationOrderEventList;

struct OrderDataKeyType
{
	int32 productid;
	int32 stationid;
	OrderDataKeyType(int32 product, int32 station):
		productid(product),
		stationid(station)
	{
	}
};

struct OrderDataKeyFuncs :
	BaseKeyFuncs<
	TPair<OrderDataKeyType, OrderList>,
	int64
	>
{
private:
	typedef BaseKeyFuncs<
		TPair<OrderDataKeyType, OrderList>,
		int64
	> Super;

public:
	typedef typename Super::ElementInitType ElementInitType;
	typedef typename Super::KeyInitType     KeyInitType;

	static KeyInitType GetSetKey(ElementInitType Element)
	{
		return (static_cast<int64>(Element.Key.productid)<<32)& static_cast<int64>(Element.Key.stationid);
	}

	static bool Matches(KeyInitType A, KeyInitType B)
	{
		return A == B;
	}

	static uint32 GetKeyHash(KeyInitType Key)
	{
		return static_cast<uint32>(Key);
	}
};
