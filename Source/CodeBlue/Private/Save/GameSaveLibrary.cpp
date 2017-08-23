// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "GameSaveLibrary.h"
#include "GameSaveData.h"

void UGameSaveLibrary::SaveGame(const FString &SaveName, const int32 Slot) {
	UGameSaveData* SaveGameInstance = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	//SaveGameInstance->PlayerName = MyPlayerName;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveName, Slot);
}

void UGameSaveLibrary::LoadGame(const int32 Slot) {
	FString slotname = FString::Printf(TEXT("Save%d"),Slot);
	if (UGameplayStatics::DoesSaveGameExist(slotname, Slot))
	{
		UGameSaveData* SaveGameInstance = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(slotname, Slot));
	}
}

