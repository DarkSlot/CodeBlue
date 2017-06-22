// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

/**
 * 
 */
class Buff
{
	
public:
	Buff();
	virtual ~Buff();
	void SetActive(const bool active);
	bool IsActive();

	virtual void Reset() {}
	virtual void Tick(float DeltaTime);

	int32 GetLevel();
protected:
	bool bActive;

	float BuffTimer;
	float BuffDecay;
	
	int32 BuffLevel;
};
