// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UGMGameInstance;
class BaseAILogic
{
public:
	BaseAILogic(int32 userId, UGMGameInstance *instance);
	virtual ~BaseAILogic();

	virtual void RunLogic(float DeltaTime) = 0;

protected:
	int32 UserId;
	float LogicCircle;
	float LogicTimer;
	UGMGameInstance *GameInstance;
};
