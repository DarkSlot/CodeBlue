// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BaseAILogic.h"

BaseAILogic::BaseAILogic(int32 userId):
	UserId(userId),
	LogicCircle(10.0f),
	LogicTimer(0.0f)
{
}

BaseAILogic::~BaseAILogic()
{
}