// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ShipManager.h"


// Sets default values
AShipManager::AShipManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}
AShipPawnBase *AShipManager::SummonTransportShip(const FVector &pos) {
	UObject* tAsset = LoadObject<UClass>(nullptr, TEXT("/Game/Ships/TransportShip/TransportShip.TransportShip_C"));
	if (!tAsset) return nullptr;
	UClass* bp = Cast<UClass>(tAsset);
	FActorSpawnParameters parameter;
	parameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FRotator rotator(FRotator::ZeroRotator);
	AShipPawnBase *ship = GetWorld()->SpawnActor<AShipPawnBase>(bp, pos, rotator, parameter);
	return ship;
}

// Called when the game starts or when spawned
void AShipManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

