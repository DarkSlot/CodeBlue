// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ManufacturerAILogic.h"
#include "../../Data/DataProcesser.h"
#include "../../GMGameInstance.h"
#include "../../Produce/ProduceCenter.h"
#include "../../Ship/ShipManager.h"
#include "../../Station/StationManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

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
			float price;
			int32 targetstaion = GameInstance->DataProcesser->GetSuitableStationByPrice(
				line->GetProductId(), true, price);
			if (targetstaion>0&& targetstaion != line->GetStationId())
			{
				//send transport ship to another station
				UStationManager *stationManager = GameInstance->StationManager;
				FVector startpos = stationManager->GetStationById(line->GetStationId())->GetActorLocation();
				startpos += FVector(1000.0f,0.0f,0.0f);
				FVector targetpos = stationManager->GetStationById(targetstaion)->GetActorLocation();
				AShipManager *shipmanager = GameInstance->CurrentShipManager;
				AShipPawnBase *ship = shipmanager->SummonTransportShip(startpos);
				if (ship)
				{
					AAIController *controller = Cast<AAIController>(ship->GetController());
					if (controller)
					{
						UBlackboardComponent *component = controller->GetBlackboardComponent();
						component->SetValueAsInt("Product", line->GetProductId());
						component->SetValueAsInt("Number", stock);
						component->SetValueAsInt("User", UserId);
						component->SetValueAsFloat("Price", price);
						component->SetValueAsObject("StartStation", stationManager->GetStationById(line->GetStationId()));
						component->SetValueAsObject("EndStation", stationManager->GetStationById(targetstaion));
					}
				}
			}
			else
			{
				GameInstance->DataProcesser->SellProduct(line->GetProductId(), item->baseprice,
					1000, UserId, line->GetStationId());
			}
		}
	}
}