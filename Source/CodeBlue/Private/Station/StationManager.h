// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StationBase.h"
#include "StationManager.generated.h"

/**
 * 
 */
UCLASS()
class UStationManager : public UObject
{
	GENERATED_BODY()
	
public:
	void RegisterStation(AStationBase *station);
	AStationBase *GetStationById(int32 stationid);
	void Clear();
	
	TArray<AStationBase *> StationList;
};
