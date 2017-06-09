// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GMGameInstance.h"
#include "BaseLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class ABaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Produce")
	UGMGameInstance *GameInstance;
};
