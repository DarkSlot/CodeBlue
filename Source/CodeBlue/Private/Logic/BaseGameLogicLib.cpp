// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BaseGameLogicLib.h"
#include "../Market/MarketProcessCore.h"
#include "../Market/Command/NewGameDataCommand.h"


//void UBaseGameLogicLib::BeginNewGame() {
//	FString actualFilename = FPaths::GameContentDir() + TEXT("/Data/Temp/running.db");
//
//	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*actualFilename))
//	{
//		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*actualFilename);
//	}
//	MarketProcessCore::StartInstance("/Data/Temp/running.db");
//	UDataTable* GameObjectLookupTable = LoadObject<UDataTable>(nullptr,
//		TEXT("/Game/Data/UserData.UserData"));
//	TArray<FUserDataTable *> rows;
//	GameObjectLookupTable->GetAllRows(TEXT("GENERAL"), rows);
//	NewGameDataCommand *command = new NewGameDataCommand(rows);
//	MarketProcessCore::GetInstance()->EnqueueCommand(command);
//}
//
//void UBaseGameLogicLib::ShutDown() {
//	MarketProcessCore::Shutdown();
//}

