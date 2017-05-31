// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BTTask_Produce.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Data/DataProcesser.h"
#include "PlayerBasePawn.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_Produce::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent* bbcomp = OwnerComp.GetBlackboardComponent();
	if (bbcomp)
	{
		APawn *pawn = OwnerComp.GetAIOwner()->GetPawn();
		APlayerBasePawn *playerpawn = Cast<APlayerBasePawn>(pawn);
		
		GameInstance = Cast<UGMGameInstance>(playerpawn->GetGameInstance());
		GameInstance->DataProcesser->ProduceProduct(1,20, playerpawn->UserId,1);
	}
	return EBTNodeResult::Succeeded;
}


