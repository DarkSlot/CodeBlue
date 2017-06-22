// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BaseLevelScriptActor.h"
#include "Ship/ShipManager.h"


void ABaseLevelScriptActor::BeginPlay() {
	Super::BeginPlay();
	GameInstance = Cast<UGMGameInstance>(GetGameInstance());
	GameInstance->CurrentShipManager = Cast<AShipManager>(GetWorld()->SpawnActor(AShipManager::StaticClass()));
}
void ABaseLevelScriptActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	GameInstance->Tick(DeltaTime);
}



