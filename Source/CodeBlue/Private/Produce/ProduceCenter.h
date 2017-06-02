// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProduceLine.h"
/**
 * 
 */
class ProduceCenter
{
public:
	ProduceCenter();
	~ProduceCenter();
	void Produce(float DeltaTime);
private:
	TArray<ProduceLine *> ProduceLineList;
};
