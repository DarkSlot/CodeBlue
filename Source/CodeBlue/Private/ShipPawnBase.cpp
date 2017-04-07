// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ShipPawnBase.h"


// Sets default values
AShipPawnBase::AShipPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 100.0f;
	Agility = 50.0f;
}

// Called when the game starts or when spawned
void AShipPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShipPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

