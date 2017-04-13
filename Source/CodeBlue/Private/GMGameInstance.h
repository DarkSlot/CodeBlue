// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Localization/ProductLocalizationList.h"
#include "Blueprint/UserWidget.h"
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

	ProductLocalizationList *ProductLocalizationList;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UUserWidget* WidgetInstance;	
};
