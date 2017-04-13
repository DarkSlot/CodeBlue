// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "StationBase.h"


// Sets default values
AStationBase::AStationBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStationBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

