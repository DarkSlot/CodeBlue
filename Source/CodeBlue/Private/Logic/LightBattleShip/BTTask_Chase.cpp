// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BTTask_Chase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Ship/ShipPawnBase.h"
#include "AIController.h"

UBTTask_Chase::UBTTask_Chase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent *component = OwnerComp.GetBlackboardComponent();
	AShipPawnBase *Target = Cast<AShipPawnBase>(component->GetValueAsObject("Target"));
	if (!Target)
	{
		return EBTNodeResult::Failed;
	}
	AAIController *aicontroller = OwnerComp.GetAIOwner();
	if (!aicontroller)
	{
		return EBTNodeResult::Failed;
	}
	AShipPawnBase *ship = Cast<AShipPawnBase>(aicontroller->GetPawn());
	if (!ship)
	{
		return EBTNodeResult::Failed;
	}
	float WeaponRange = component->GetValueAsFloat("WeaponRange");

	FBTChaseMemory *cache = (FBTChaseMemory *)(NodeMemory);
	cache->Target = Target;
	cache->SelfShip = ship;
	cache->WeaponRange = WeaponRange;

	FVector delta = Target->GetActorLocation() - ship->GetActorLocation();
	float distance = delta.SizeSquared();
	if (distance<WeaponRange*WeaponRange)
	{
		return EBTNodeResult::Succeeded;
	}

	aicontroller->SetFocalPoint(Target->GetActorLocation(), EAIFocusPriority::Move);
	EPathFollowingRequestResult::Type result = aicontroller->MoveToActor(Target);
	if (result == EPathFollowingRequestResult::Failed)
	{
		delta.Normalize();
		Target->AddMovementInput(delta, 1.0f);
	}

	return EBTNodeResult::InProgress;
}
uint16 UBTTask_Chase::GetInstanceMemorySize() const {
	return sizeof(FBTChaseMemory);
}
void UBTTask_Chase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	FBTChaseMemory *cache = (FBTChaseMemory *)(NodeMemory);
	FVector delta = cache->Target->GetActorLocation() - cache->SelfShip->GetActorLocation();
	float distance = delta.SizeSquared();
	if (distance<cache->WeaponRange*cache->WeaponRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	//AAIController *aicontroller = Cast<AAIController>(cache->SelfShip->GetController());
	//aicontroller->SetFocalPoint(cache->Target->GetActorLocation(), EAIFocusPriority::Move);
	//EPathFollowingRequestResult::Type result = aicontroller->MoveToActor(cache->Target);
}