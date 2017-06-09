// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "AILogicManager.h"

UAILogicManager::UAILogicManager()
{
}

UAILogicManager::~UAILogicManager()
{
}
void UAILogicManager::Init(UDataProcesser *dataProcesser) {

}
void UAILogicManager::ProcessLogicUnits(float DeltaTime) {
	for (auto unit: LogicUnits)
	{
		unit->RunLogic(DeltaTime);
	}
}
