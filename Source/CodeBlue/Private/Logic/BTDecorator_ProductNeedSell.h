// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ProductNeedSell.generated.h"

/**
 * 
 */
UCLASS()
class UBTDecorator_ProductNeedSell : public UBTDecorator
{
	GENERATED_BODY()
protected:
virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
	
};
