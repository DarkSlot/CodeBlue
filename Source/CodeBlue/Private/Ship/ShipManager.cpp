// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ShipManager.h"


// Sets default values
AShipManager::AShipManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

