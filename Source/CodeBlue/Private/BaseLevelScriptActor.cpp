// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BaseLevelScriptActor.h"


void ABaseLevelScriptActor::BeginPlay() {
	Super::BeginPlay();
	GameInstance = Cast<UGMGameInstance>(GetGameInstance());
}
void ABaseLevelScriptActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	GameInstance->Tick(DeltaTime);
}



