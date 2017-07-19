// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Localization/ProductLocalizationList.h"
#include "Blueprint/UserWidget.h"
#include "Data/DataProcesser.h"
#include "Produce/ProduceCenter.h"
#include "Logic/AILogicManager.h"
#include "Ship/ShipManager.h"
#include "Station/StationManager.h"
#include "GMGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UGMGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UGMGameInstance();
	virtual ~UGMGameInstance();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateGameUI();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void CreateNewGameData();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void LoadGameDatabase();

	void Tick(float DeltaTime);

	ProductLocalizationList *ProductLocalizationList;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UUserWidget* WidgetInstance;	

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	UDataProcesser *DataProcesser;

	UPROPERTY(BlueprintReadWrite, Category = "Produce")
	UProduceCenter *ProduceCenter;

	UPROPERTY(BlueprintReadWrite, Category = "Logic")
	UAILogicManager *AILogicManager;

	UPROPERTY(BlueprintReadWrite, Category = "Station")
	UStationManager *StationManager;
	
	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int32 MainUserId;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	AShipManager *CurrentShipManager;
};
