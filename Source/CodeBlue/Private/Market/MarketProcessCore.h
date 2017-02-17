// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Core.h"
#include "Command/MarketCommand.h"
#include <thread>
#include <mutex>
/**
 * 
 */
class MarketProcessCore
{
public:
	MarketProcessCore();
	virtual ~MarketProcessCore();
	
	static MarketProcessCore *StartGetInstance();
	static void Shutdown();
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static  MarketProcessCore* Instance;

	std::mutex CommandMutex;
	TArray<MarketCommand *> CommandList;

	void EnqueueCommand(MarketCommand *command);
};
