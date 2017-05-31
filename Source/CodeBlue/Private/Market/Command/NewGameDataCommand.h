// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MarketCommand.h"
#include "../UserDataTable.h"
/**
 * 
 */
class NewGameDataCommand : public MarketCommand
{
public:
	NewGameDataCommand(TArray<FUserDataTable *> info);
	virtual ~NewGameDataCommand();
	virtual void Execute() override;
private:
	void CreateUserInfo();

	TArray<FUserDataTable> userinfo;
};
