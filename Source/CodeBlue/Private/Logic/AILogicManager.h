// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "BaseAILogic.h"
#include "AILogicManager.generated.h"

/**
 * 
 */
class UGMGameInstance;
UCLASS()
class UAILogicManager : public UObject
{
	GENERATED_BODY()
public:
	UAILogicManager();
	~UAILogicManager();

	void Init(UGMGameInstance *instance);

	void AddLogicUnit(BaseAILogic *unit);
	void ProcessLogicUnits(float DeltaTime);
private:
	UGMGameInstance *GameInstance;
	TArray<BaseAILogic *> LogicUnits;
};
