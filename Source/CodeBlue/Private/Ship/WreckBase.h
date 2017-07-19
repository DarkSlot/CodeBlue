// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipPawnBase.h"
#include "WreckBase.generated.h"

/**
 * 
 */
UCLASS()
class AWreckBase : public AShipPawnBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Ship)
	virtual	bool ReduceCargo(int32 productid, int32 num) override;
	
	
};
