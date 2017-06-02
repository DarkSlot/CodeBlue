// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ProduceCenter.h"

ProduceCenter::ProduceCenter()
{
}

ProduceCenter::~ProduceCenter()
{
}
void ProduceCenter::Produce(float DeltaTime) {
	for (auto line: ProduceLineList)
	{
		line->Produce(DeltaTime);
	}
}
