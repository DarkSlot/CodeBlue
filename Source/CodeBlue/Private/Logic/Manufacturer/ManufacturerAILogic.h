// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../BaseAILogic.h"

/**
 * 
 */
class ManufacturerAILogic : public BaseAILogic
{
public:
	ManufacturerAILogic(int32 UserId);
	virtual ~ManufacturerAILogic();

	virtual void RunLogic(float DeltaTime) override;
};
