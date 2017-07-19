// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PackageDealer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UPackageDealer : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Data)
	virtual void RemovePackageItem() {}
	
	
};
