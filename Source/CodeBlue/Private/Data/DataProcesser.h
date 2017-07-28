// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "OrderDataItem.h"
#include "UserDataItem.h"
#include "PropertyDataItem.h"
#include "ProductInfoItem.h"
#include "StationInfoDataItem.h"
#include "SQLiteLibrary.h"
#include "DataProcesser.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class UDataProcesser : public UObject
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderListChanged, const int32, StationId, const int32, ProductId);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserMoneyChanged, const int32, UserId, const float, Money);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPropertyChanged, const int32, StationId, const int32, ProductId,const int32, UserId);

	UFUNCTION(BlueprintCallable, Category = "Data")
	void BuyProduct(const int32 productid, const float price, const int32 num,
			const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	void SellProduct(const int32 productid, const float price, const int32 num,
			const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	void AddOrder(const int32 ordertype,const int32 productid, const float price, const int32 num,
		const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	void RemoveOrder(const int32 orderid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	void CancelOrder(const int32 orderid);


	UFUNCTION(BlueprintCallable, Category = "Data")
	void UpdateOrderPrice(const int32 orderid,const float price);

	UFUNCTION(BlueprintCallable, Category = "Data")
	bool AddProperty(const int32 productid, const int32 num,
			const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	bool ReduceProperty(const int32 productid, const int32 num,
			const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = Ship)
	TMap<int32, int32> GetStationProperty(const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	bool AddMoney(const float num,const int32 userid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	bool CostMoney(const float num,const int32 userid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	float CheckMoney(const int32 userid);

	UFUNCTION(BlueprintCallable, Category = "Data")
	int32 CheckProductStock(const int32 productid, const int32 userid, const int32 stationid);

	UFUNCTION(BlueprintCallable, Category = "Data")
		UTexture2D *GetProductIcon(const int32 productid);

	UPROPERTY(BlueprintCallable,BlueprintAssignable, Category = "Data")
	FOnOrderListChanged OnOrderListChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Data")
	FOnUserMoneyChanged OnUserMoneyChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Data")
	FOnPropertyChanged FOnPropertyChanged;
	
	void Init();

	bool GetProductOrder(const int32 productid, const int32 stationid, OrderList &list);
	bool GetProductOrderByPrice(const int32 productid, const int32 stationid,
		bool isHighest, FOrderDataItem &item);
	bool GetProductOrderByUser(const int32 productid, const int32 stationid,
		const int32  userid, OrderList &list);
	//get the highest buyer station or the lowest seller station
	int32 GetSuitableStationByPrice(const int32 productid, bool isHighest,float &price);
	//sum the num of orders
	int32 CountOrderNum(const int32 productid, const int32 userid,
		const int32 stationid);
	//change all order price of the same station and user
	int32 ChangeOrderPriceByUserStation(const int32 productid, const int32 userid,
		const int32 stationid,const float price);
	UserList &GetUserData();
	TMap<int32, FProductInfoItem *> &GetProductInfo();
	StationInfoList &GetStationData();
	FString GetProductName(const int32 productid);
	int32 CreateNewUser(FUserDataItem &item);
private:
	//TMap<OrderDataKeyType, OrderList, FDefaultSetAllocator, OrderDataKeyFuncs> OrderData;
	UPROPERTY(VisibleAnywhere,Category = "Data")
	USQLiteLibrary *SqliteLib;

	//StationOrderList OrderData;
	//TArray<int32> RemovedOrderList;
	OrderRemoveEventList OrderRemoveListeners;
	UserList UserData;
	//UserPropertyList PropertyData;
	TMap<int32, FProductInfoItem *> ProductInfo;
	StationInfoList StationData;
	//StationOrderEventList OrderEventData;

	//void RemoveOrder(FOrderDataItem *order);
	void UpdateOrderNum(const int32 orderid, const int32 num);
};
