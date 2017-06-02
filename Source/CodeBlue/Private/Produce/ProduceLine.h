// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UDataProcesser;
class ProduceLine
{
public:
	ProduceLine(int32 user,int32 station,int32 product,float basecircletime,
		float basecircleproduction);
	~ProduceLine();

	void Produce(float DeltaTime);
private:
	//Owner of the Produce Line
	int32 UserId;
	//Location of the Produce Line
	int32 StationId;
	//Production of the Produce Line
	int32 ProductId;
	//base circle time;
	float BaseCircleTime;
	//circle time rate;
	float CircleTimeRate;
	//circle time rate;
	float CircleTime;
	//base produced every cricle
	float BaseCircleProduction;
	//produce rate
	float CircleProductionRate;
	//produce rate
	int32 CircleProduction;

	float Timer;

	UDataProcesser *DataProcesser;
};
