// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameSaveLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UGameSaveLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()	
public:
	UFUNCTION(BlueprintCallable, Category = "Save")
	static void SaveGame(const FString &SaveName,const int32 Slot);
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	static void LoadGame(const int32 Slot);
};
