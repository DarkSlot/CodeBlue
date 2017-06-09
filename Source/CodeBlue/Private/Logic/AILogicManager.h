// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "BaseAILogic.h"
#include "AILogicManager.generated.h"

/**
 * 
 */
class UDataProcesser;
UCLASS()
class UAILogicManager : public UObject
{
	GENERATED_BODY()
public:
	UAILogicManager();
	~UAILogicManager();

	void Init(UDataProcesser *dataProcesser);

	void ProcessLogicUnits(float DeltaTime);
private:
	TArray<BaseAILogic *> LogicUnits;
};
