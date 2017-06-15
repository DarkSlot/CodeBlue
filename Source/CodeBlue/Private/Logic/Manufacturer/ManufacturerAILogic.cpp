// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ManufacturerAILogic.h"
#include "../../Data/DataProcesser.h"
#include "../../GMGameInstance.h"
#include "../../Produce/ProduceCenter.h"

ManufacturerAILogic::ManufacturerAILogic(int32 UserId, UGMGameInstance *instance):
	BaseAILogic(UserId, instance)
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
		LogicTimer -= LogicCircle;
		ProcessLogic();
	}
}

void ManufacturerAILogic::ProcessLogic() {
	TArray<ProduceLine *> lines;
	GameInstance->ProduceCenter->FindProduceLineByUser(UserId, lines);
	TMap<int32, FProductInfoItem *> ProductInfo = GameInstance->DataProcesser->GetProductInfo();
	for (auto line: lines)
	{
		int32 stock = GameInstance->DataProcesser->CheckProductStock(line->GetProductId(),
			UserId, line->GetStationId());
		if (stock>1000)
		{
			FProductInfoItem *item = ProductInfo[line->GetProductId()];
			GameInstance->DataProcesser->SellProduct(line->GetProductId(), item->baseprice,
				1000,UserId, line->GetStationId());
		}
	}
}