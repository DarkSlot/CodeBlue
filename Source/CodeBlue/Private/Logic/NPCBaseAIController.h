// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "NPCBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class ANPCBaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	ANPCBaseAIController(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;
	
	
	
};
