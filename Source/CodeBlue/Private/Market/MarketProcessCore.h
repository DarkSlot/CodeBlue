// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Core.h"
#include "Command/MarketCommand.h"
#include <thread>
#include <mutex>
#include <atomic>
/**
 * 
 */
class MarketProcessCore
{
public:
	MarketProcessCore(const FString &filename);
	virtual ~MarketProcessCore();
	
	static MarketProcessCore *StartInstance(const FString &filename);
	static MarketProcessCore *GetInstance();
	static void Shutdown();

	void EnqueueCommand(MarketCommand *command);
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static  MarketProcessCore* Instance;

	enum ERunningState :int8
	{
		RUNNING,
		STOPING,
		STOPED
	};
	std::atomic_int8_t RunningState;
	TQueue<MarketCommand *> CommandList;
	void Stop();
	void ProcessCommand();
};
