// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "StationBase.h"
#include "Data/DataProcesser.h"
#include "GMGameInstance.h"


// Sets default values
AStationBase::AStationBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStationBase::BeginPlay()
{
	Super::BeginPlay();
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(GetGameInstance());
	DataProcesser = GameInstance->DataProcesser;
	StationInfoList &InfoMap = GameInstance->DataProcesser->GetStationData();
	FStationInfoDataItem* item = InfoMap[StationId];
	FoodCost = item->FoodCost;
	FuelCost = item->FuelCost;
	CostTimer = 0.0f;
}

// Called every frame
void AStationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_BuffStarving.IsActive())
	{
		m_BuffStarving.Tick(DeltaTime);
	}
	CostTimer += DeltaTime;
	if (CostTimer>100.0f)
	{
		CostTimer -= 100.0f;

		if (DataProcesser->CheckProductStock(2, StationId, StationId) < FoodCost*500)
		{	
			DealFoodShortage(m_BuffStarving.GetLevel());
		}
		//if (DataProcesser->CheckProductStock(3, StationId, StationId) < FuelCost * 500)
		//{
		//	DataProcesser->BuyProduct(3, DataProcesser->GetProductInfo()[3]->baseprice,
		//		FuelCost * 1000, StationId, StationId);
		//}
		if (DataProcesser->CostProduct(2, FoodCost * 10, StationId, StationId))
		{
			m_BuffStarving.SetActive(false);
			m_BuffStarving.Reset();
		}
		else
		{
			m_BuffStarving.SetActive(true);
		}
		//DataProcesser->CostProduct(3, FuelCost * 10, StationId, StationId);
	}
}

void AStationBase::DealFoodShortage(int32 starvinglvl) {
	float price = (starvinglvl*0.1f + 1.0f)*
		DataProcesser->GetProductInfo()[2]->baseprice;

	OrderList list;
	DataProcesser->GetProductOrder(2, StationId, StationId, list);
	int32 totalOrderNum = 0;
	for (auto &order: list)
	{
		totalOrderNum += order->stock;
		order->price = price;
	}
	if (totalOrderNum<1000)
	{
		DataProcesser->BuyProduct(2, price,
			FoodCost * 1000, StationId, StationId);
	}
}
