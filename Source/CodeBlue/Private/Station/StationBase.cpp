// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "StationBase.h"
#include "../Data/DataProcesser.h"
#include "../GMGameInstance.h"
#include "../Station/StationManager.h"


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
	FoodCostData = 0.0f;
	Incoming = 100.0f;
	LastStarvingLevel = 0;
	FUserDataItem *useritem = DataProcesser->GetUserData().Find(StationId);
	if (useritem)
	{
		StationName = useritem->username;
	}
	GameInstance->StationManager->RegisterStation(this);
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
	if (CostTimer>1.0f)
	{
		CostTimer -= 1.0f;

		if (DataProcesser->CheckProductStock(2, StationId, StationId) < FoodCost*60)
		{	
			DealFoodShortage(m_BuffStarving.GetLevel());
		}
		FoodCostData += FoodCost;
		int32 OnetimeFoodCost = FMath::FloorToInt(FoodCostData);
		FoodCostData -= OnetimeFoodCost;
		if (DataProcesser->ReduceProperty(2, OnetimeFoodCost, StationId, StationId))
		{
			if (m_BuffStarving.IsActive())
			{
				m_BuffStarving.SetActive(false);
				m_BuffStarving.Reset();
				DealFoodShortage(m_BuffStarving.GetLevel());
			}
		}
		else
		{
			m_BuffStarving.SetActive(true);
		}
		DataProcesser->AddMoney(Incoming, StationId);
		if (InfoChange.IsBound())
		{
			FoodStock = DataProcesser->CheckProductStock(2, StationId, StationId);
			Money = DataProcesser->CheckMoney(StationId);
			InfoChange.Broadcast(FoodStock, 0.0f, Money);
		}
	}
}

void AStationBase::DealFoodShortage(int32 starvinglvl) {
	float price = (starvinglvl*0.1f + 1.0f)*
		DataProcesser->GetProductInfo()[2]->baseprice;	
	if (LastStarvingLevel!= starvinglvl)
	{
		LastStarvingLevel = starvinglvl;
		OrderList list;
		DataProcesser->GetProductOrderByUser(2, StationId, StationId, list);
		for (auto &item:list)
		{
			DataProcesser->CancelOrder(item.orderid);
		}
		DataProcesser->BuyProduct(2, price,
			FoodCost * 120, StationId, StationId);
	}
	else
	{
		int32 totalOrderNum = DataProcesser->CountOrderNum(2, StationId, StationId);
		if (totalOrderNum<FoodCost * 120)
		{
			DataProcesser->BuyProduct(2, price,
				FoodCost * 120, StationId, StationId);
		}
	}
}
