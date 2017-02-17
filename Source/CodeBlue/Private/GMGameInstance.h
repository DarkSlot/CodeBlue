// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Localization/ProductLocalizationList.h"
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

	ProductLocalizationList *ProductLocalizationList;
	
};
