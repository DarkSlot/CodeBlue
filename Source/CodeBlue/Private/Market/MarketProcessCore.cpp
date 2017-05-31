// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "MarketProcessCore.h"
//#include "SQLiteDatabase.h"

MarketProcessCore* MarketProcessCore::Instance = nullptr;
MarketProcessCore::MarketProcessCore(const FString &filename)
{
	//USQLiteDatabase::RegisterDatabase(TEXT("market"), filename/*TEXT("/Data/market.db")*/, true);
	RunningState = RUNNING;
	UE_LOG(CodeBlueLog, Verbose,TEXT("Market Thread Start"));
}

MarketProcessCore::~MarketProcessCore()
{
	UE_LOG(CodeBlueLog, Verbose, TEXT("Market Thread Stopped"));
}
MarketProcessCore *MarketProcessCore::StartInstance(const FString &filename) {
	if (!Instance&& FPlatformProcess::SupportsMultithreading())
	{
		Instance = new MarketProcessCore(filename);
		std::thread MainThread(&MarketProcessCore::ProcessCommand, Instance);
		MainThread.detach();
	}
	return Instance;
}
MarketProcessCore *MarketProcessCore::GetInstance() {
	return Instance;
}
void MarketProcessCore::Shutdown() {
	if (Instance)
	{
		Instance->Stop();
		delete Instance;
		Instance = nullptr;
	}
}
void MarketProcessCore::Stop() {
	RunningState = STOPING;
	while (RunningState != STOPED)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
void MarketProcessCore::EnqueueCommand(MarketCommand *command) {
	CommandList.Enqueue(command);
}
void MarketProcessCore::ProcessCommand() {
	while (RunningState == RUNNING)
	{
		if (!CommandList.IsEmpty())
		{
			MarketCommand *command;
			CommandList.Dequeue(command);
			command->Execute();
			delete command;
		}
	}
	RunningState = STOPED;
}