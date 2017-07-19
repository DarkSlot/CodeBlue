// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PackageDealer.h"
#include "../Station/StationBase.h"
#include "PackageDealerStation.generated.h"

/**
 * 
 */
UCLASS()
class UPackageDealerStation : public UPackageDealer
{
	GENERATED_BODY()
	
public:
	virtual void RemovePackageItem() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Station)
		AStationBase *Station;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Station)
		int32 productid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Station)
		int32 number;
};
