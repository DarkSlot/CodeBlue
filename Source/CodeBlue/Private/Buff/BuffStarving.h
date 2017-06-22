// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"

/**
 * 
 */
class BuffStarving : public Buff
{

public:
	BuffStarving();
	virtual ~BuffStarving();

	virtual void Reset() override;
	virtual void Tick(float DeltaTime) override;
	
	
	
};
