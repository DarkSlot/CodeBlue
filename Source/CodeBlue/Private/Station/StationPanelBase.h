// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StationBase.h"
#include "StationPanelBase.generated.h"

/**
 * 
 */
UCLASS()
class UStationPanelBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Station")
	void InitStationInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market")
	AStationBase *CurrentStation;
	
};
