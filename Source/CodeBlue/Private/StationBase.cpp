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
	TArray<FStationTradeDataItem *> stationInfoList;
	StationTradeList &InfoMap = GameInstance->DataProcesser->GetStationTradeInfo();
	InfoMap.MultiFind(StationId, stationInfoList);
	for (auto info: stationInfoList)
	{
		if (info->isBuy == 0)
		{

		}
	}
}

// Called every frame
void AStationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

