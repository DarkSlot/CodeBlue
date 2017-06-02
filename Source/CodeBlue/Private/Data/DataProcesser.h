// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "OrderDataItem.h"
#include "UserDataItem.h"
#include "PropertyDataItem.h"
#include "ProductInfoItem.h"
#include "DataProcesser.generated.h"


/**
 * 
 */
UCLASS()
class UDataProcesser : public UObject
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderListChanged, const int32, StationId, const int32, ProductId);

	UFUNCTION(BlueprintCallable, Category = "Data")
	void BuyProduct(const int32 productid, const float price, const int32 num,
			const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	void SellProduct(const int32 productid, const float price, const int32 num,
			const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	bool ProduceProduct(const int32 productid,const int32 num,
			const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	bool CostProduct(const int32 productid, const int32 num,
			const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	int32 CheckProductStock(const int32 productid, const int32 userid, const int32 stationid);

	UPROPERTY(BlueprintCallable,BlueprintAssignable, Category = "Data")
	FOnOrderListChanged OnOrderListChanged;	
	
	void Init();
	bool GetProductOrder(const int32 productid, const int32 stationid, OrderList **list);
	TMap<int32, FProductInfoItem *> &GetProductInfo();
	//StationTradeList &GetStationTradeInfo();
	FString GetProductName(const int32 productid);
private:
	//TMap<OrderDataKeyType, OrderList, FDefaultSetAllocator, OrderDataKeyFuncs> OrderData;
	StationOrderList OrderData;
	TArray<int32> RemovedOrderList;
	OrderRemoveEventList OrderRemoveListeners;
	UserList UserData;
	UserPropertyList PropertyData;
	TMap<int32, FProductInfoItem *> ProductInfo;
	//StationTradeList StationTradeInfo;
	//StationOrderEventList OrderEventData;

	void RemoveOrder(FOrderDataItem *order);
};
