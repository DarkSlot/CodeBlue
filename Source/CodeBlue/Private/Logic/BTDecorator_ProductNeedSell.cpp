// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BTDecorator_ProductNeedSell.h"
#include "../Data/DataProcesser.h"
#include "PlayerBasePawn.h"
#include "AIController.h"
#include "../GMGameInstance.h"



bool UBTDecorator_ProductNeedSell::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	UBlackboardComponent* bbcomp = OwnerComp.GetBlackboardComponent();
	if (bbcomp)
	{
		APawn *pawn = OwnerComp.GetAIOwner()->GetPawn();
		APlayerBasePawn *playerpawn = Cast<APlayerBasePawn>(pawn);

		UGMGameInstance *GameInstance = Cast<UGMGameInstance>(playerpawn->GetGameInstance());
		int32 stock = GameInstance->DataProcesser->CheckProductStock(1, playerpawn->UserId, 1);

		UE_LOG(CodeBlueLog, Log, TEXT("Stock:%d"), stock);
		if (stock>=500)
		{
			return true;
		}
	}
	return false;
}
