// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MarketProcessCore.h"
#include "SQLiteDatabase.h"

MarketProcessCore* MarketProcessCore::Instance = nullptr;
MarketProcessCore::MarketProcessCore()
{
	USQLiteDatabase::RegisterDatabase(TEXT("market"), TEXT("/Data/market.db"), true);
	UE_LOG(CodeBlueLog, Verbose,TEXT("Market Thread Start"));
}

MarketProcessCore::~MarketProcessCore()
{
	UE_LOG(CodeBlueLog, Verbose, TEXT("Market Thread Stopped"));
}

MarketProcessCore *MarketProcessCore::StartGetInstance() {
	if (!Instance&& FPlatformProcess::SupportsMultithreading())
	{
		Instance = new MarketProcessCore();
	}
	return Instance;
}
void MarketProcessCore::Shutdown() {
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}
void MarketProcessCore::EnqueueCommand(MarketCommand *command) {
	CommandMutex.lock();
	CommandList.Push(command);
	CommandMutex.unlock();
}