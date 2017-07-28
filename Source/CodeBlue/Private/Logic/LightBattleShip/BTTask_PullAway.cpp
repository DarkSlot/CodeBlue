// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BTTask_PullAway.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Ship/ShipPawnBase.h"
#include "AIController.h"

UBTTask_PullAway::UBTTask_PullAway(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTask_PullAway::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent *component = OwnerComp.GetBlackboardComponent();
	AShipPawnBase *Target = Cast<AShipPawnBase>(component->GetValueAsObject("Target"));
	AAIController *aicontroller = OwnerComp.GetAIOwner();
	AShipPawnBase *ship = Cast<AShipPawnBase>(aicontroller->GetPawn());
	float WeaponRange = component->GetValueAsFloat("WeaponRange");

	FBTPullAwayMemory *cache = (FBTPullAwayMemory *)(NodeMemory);
	cache->Target = Target;
	cache->SelfShip = ship;
	cache->WeaponRange = WeaponRange;

	FVector delta = Target->GetActorLocation() - ship->GetActorLocation();
	float distance = delta.Size();
	if (distance>WeaponRange)
	{
		return EBTNodeResult::Succeeded;
	}

	FVector targetpos = Target->GetActorLocation() + Target->GetActorRightVector()*WeaponRange*2;
	aicontroller->SetFocalPoint(targetpos, EAIFocusPriority::Move);
	EPathFollowingRequestResult::Type result = aicontroller->MoveToLocation(targetpos, 10.0f);

	return EBTNodeResult::InProgress;
}
uint16 UBTTask_PullAway::GetInstanceMemorySize() const {
	return sizeof(FBTPullAwayMemory);
}
void UBTTask_PullAway::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	FBTPullAwayMemory *cache = (FBTPullAwayMemory *)(NodeMemory);
	FVector delta = cache->Target->GetActorLocation() - cache->SelfShip->GetActorLocation();
	float distance = delta.SizeSquared();
	if (distance>cache->WeaponRange*cache->WeaponRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	FVector targetpos = cache->Target->GetActorLocation() + cache->Target->GetActorRightVector()*cache->WeaponRange * 2;
	AAIController *aicontroller = Cast<AAIController>(cache->SelfShip->GetController());
	aicontroller->SetFocalPoint(targetpos, EAIFocusPriority::Move);
	EPathFollowingRequestResult::Type result = aicontroller->MoveToLocation(targetpos, 10.0f);
	if (result == EPathFollowingRequestResult::Failed)
	{
		cache->Target->AddMovementInput(cache->Target->GetActorForwardVector(), 1.0f);
	}
}