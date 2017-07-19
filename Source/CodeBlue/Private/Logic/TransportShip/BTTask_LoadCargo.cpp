// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BTTask_LoadCargo.h"
#include "../../GMGameInstance.h"
#include "../../Data/DataProcesser.h"
#include "../../Station/StationManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_LoadCargo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent *component = OwnerComp.GetBlackboardComponent();
	int32 user = component->GetValueAsInt("User");
	int32 product = component->GetValueAsInt("Product");
	int32 number = component->GetValueAsInt("Number");
	AStationBase *station = Cast<AStationBase>(component->GetValueAsObject("StartStation"));
	UGMGameInstance *GameInstance = Cast<UGMGameInstance>(OwnerComp.GetAIOwner()->GetGameInstance());
	GameInstance->DataProcesser->ReduceProperty(product, number, user, station->StationId);
	AShipPawnBase *ship = Cast<AShipPawnBase>(OwnerComp.GetAIOwner()->GetPawn());
	ship->AddCargo(product, number);
	return EBTNodeResult::Succeeded;
}


