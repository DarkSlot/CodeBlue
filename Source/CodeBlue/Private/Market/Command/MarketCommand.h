// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Core.h"

/**
 * 
 */
class MarketCommand
{
public:
	MarketCommand();
	virtual ~MarketCommand();

	virtual void Execute() = 0;
private:
};
