// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ProduceLine.h"
#include "../GMGameInstance.h"
#include "../Data/DataProcesser.h"

ProduceLine::ProduceLine(UDataProcesser *processer, int32 lineid, int32 user, int32 station, int32 product, float basecircletime,
	float basecircleproduction):
	ProduceLineId(lineid),
	DataProcesser(processer),
	UserId(user),
	StationId(station),
	ProductId(product),
	BaseCircleTime(basecircletime),
	BaseCircleProduction(basecircleproduction)
{
	CircleTimeRate = 1.0f;
	CircleTime = BaseCircleTime*CircleTimeRate;
	CircleProductionRate = 1.0f;
	CircleProduction = FMath::FloorToInt(BaseCircleProduction*CircleProductionRate);
	Timer = 0.0f;
}

ProduceLine::~ProduceLine()
{
}
int32 ProduceLine::GetLineId() {
	return ProduceLineId;
}
int32 ProduceLine::GetUserId() {
	return UserId;
}
int32 ProduceLine::GetStationId() {
	return StationId;
}
int32 ProduceLine::GetProductId() {
	return ProductId;
}
void ProduceLine::Produce(float DeltaTime) {
	Timer += DeltaTime;
	if (Timer>= CircleTime)
	{
		Timer -= CircleTime;
		DataProcesser->AddProperty(ProductId, CircleProduction, UserId, StationId);
	}
}
