// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ManufacturerAILogic.h"

ManufacturerAILogic::ManufacturerAILogic(int32 UserId):
	BaseAILogic(UserId)
{
}

ManufacturerAILogic::~ManufacturerAILogic()
{
}

void ManufacturerAILogic::RunLogic(float DeltaTime)
{
	LogicTimer += DeltaTime;
	if (LogicTimer>LogicCircle)
	{

	}
}
