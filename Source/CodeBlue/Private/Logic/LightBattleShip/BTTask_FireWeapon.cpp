// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BTTask_FireWeapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Ship/ShipPawnBase.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_FireWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AAIController *aicontroller = OwnerComp.GetAIOwner();
	AShipPawnBase *ship = Cast<AShipPawnBase>(aicontroller->GetPawn());
	ship->StartFireWeapon();
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_FireWeapon::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AAIController *aicontroller = OwnerComp.GetAIOwner();
	AShipPawnBase *ship = Cast<AShipPawnBase>(aicontroller->GetPawn());
	ship->StopFireWeapon();
	return EBTNodeResult::Aborted;
}