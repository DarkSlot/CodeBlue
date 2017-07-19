// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "PackageDealerStation.h"
#include "../Data/DataProcesser.h"
#include "../GMGameInstance.h"


void UPackageDealerStation::RemovePackageItem() {
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(Station->GetGameInstance());
	UDataProcesser *DataProcesser = GameInstance->DataProcesser;
	DataProcesser->ReduceProperty(productid, number,0, Station->StationId);
}

