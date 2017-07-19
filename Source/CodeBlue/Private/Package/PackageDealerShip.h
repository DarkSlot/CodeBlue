// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PackageDealer.h"
#include "../Ship/ShipPawnBase.h"
#include "PackageDealerShip.generated.h"

/**
 * 
 */
UCLASS()
class UPackageDealerShip : public UPackageDealer
{
	GENERATED_BODY()
	
public:
	virtual void RemovePackageItem() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
	AShipPawnBase *ship;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
		int32 productid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
		int32 number;
};
