// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "WreckBase.h"

bool AWreckBase::ReduceCargo(int32 productid, int32 num)
{
	Super::ReduceCargo(productid, num);
	if (Cargo.Num() == 0)
	{
		Destroy();
	}
	return true;
}


