// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "../GMGameInstance.h"
#include "BTTask_Produce.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_Produce : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:

	UGMGameInstance *GameInstance;
	
};
