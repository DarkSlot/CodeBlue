// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "StationManager.h"

void UStationManager::RegisterStation(AStationBase *station) {
	StationList.Add(station);
}
AStationBase *UStationManager::GetStationById(int32 stationid) {
	for (auto &station: StationList)
	{
		if (station->StationId == stationid)
		{
			return station;
		}
	}
	return nullptr;
}
void UStationManager::Clear() {
	StationList.Empty();
}