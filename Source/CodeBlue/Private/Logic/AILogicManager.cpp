// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "AILogicManager.h"
#include "../Data/DataProcesser.h"
#include "../GMGameInstance.h"
#include "Manufacturer/ManufacturerAILogic.h"

UAILogicManager::UAILogicManager()
{
}

UAILogicManager::~UAILogicManager()
{
	for (auto unit : LogicUnits)
	{
		delete unit;
	}
	LogicUnits.Empty();
}
void UAILogicManager::Init(UGMGameInstance *instance) {
	GameInstance = instance;
	UserList &userData = GameInstance->DataProcesser->GetUserData();
	for (auto item: userData)
	{
		switch (item.Value.AIType)
		{
		case 0:
			break;
		case 1:
			AddLogicUnit(new ManufacturerAILogic(item.Value.userid, GameInstance));
			break;
		default:
			break;
		}
	}
}
void UAILogicManager::AddLogicUnit(BaseAILogic *unit) {
	LogicUnits.Add(unit);
}
void UAILogicManager::ProcessLogicUnits(float DeltaTime) {
	for (auto unit: LogicUnits)
	{
		unit->RunLogic(DeltaTime);
	}
}
