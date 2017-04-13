// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StationBase.generated.h"

USTRUCT(BlueprintType)
struct FStationTradingItem
{
	GENERATED_USTRUCT_BODY()

	/** The product id of the trading item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Station)
	int32 ProductId;

	/** If the station limit the trading price. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Station)
	bool bLimitPrice;

	/** The  limited price of the trading item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Station)
	float LimitedPrice;

	FStationTradingItem()
		: ProductId(0)
		, bLimitPrice(false)
		, LimitedPrice(0.0f)
	{
	}
};
UCLASS()
class CODEBLUE_API AStationBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStationBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FStationTradingItem> BuyList;
	TArray<FStationTradingItem> SellList;
	
};
