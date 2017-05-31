// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BTTask_SellProduct.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Data/DataProcesser.h"
#include "PlayerBasePawn.h"
#include "AIController.h"
#include "../GMGameInstance.h"

EBTNodeResult::Type UBTTask_SellProduct::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent* bbcomp = OwnerComp.GetBlackboardComponent();
	if (bbcomp)
	{
		APawn *pawn = OwnerComp.GetAIOwner()->GetPawn();
		APlayerBasePawn *playerpawn = Cast<APlayerBasePawn>(pawn);

		UGMGameInstance *GameInstance = Cast<UGMGameInstance>(playerpawn->GetGameInstance());
		GameInstance->DataProcesser->SellProduct(1,20.0f,
			GameInstance->DataProcesser->CheckProductStock(1, playerpawn->UserId, 1), playerpawn->UserId, 1);
	}
	return EBTNodeResult::Succeeded;
}


