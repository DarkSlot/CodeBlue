// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BTTask_Aim.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Ship/ShipPawnBase.h"
#include "AIController.h"

UBTTask_Aim::UBTTask_Aim(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTask_Aim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent *component = OwnerComp.GetBlackboardComponent();
	AShipPawnBase *Target = Cast<AShipPawnBase>(component->GetValueAsObject("Target"));
	AAIController *aicontroller = OwnerComp.GetAIOwner();
	AShipPawnBase *ship = Cast<AShipPawnBase>(aicontroller->GetPawn());
	float WeaponSpeed = component->GetValueAsFloat("WeaponSpeed");
	float ReorganizeRange = component->GetValueAsFloat("ReorganizeRange");

	FBTAimApproachMemory *cache = (FBTAimApproachMemory *)(NodeMemory);
	cache->Target = Target;
	cache->SelfShip = ship;
	cache->WeaponSpeed = WeaponSpeed;
	cache->ReorganizeRange = ReorganizeRange;

	FVector delta = Target->GetActorLocation() - ship->GetActorLocation();
	float distance = delta.Size();
	if (distance<ReorganizeRange)
	{
		return EBTNodeResult::Succeeded;
	}

	float bullettime = distance / WeaponSpeed;
	FVector targetpos = Target->GetActorLocation() + Target->GetVelocity()*bullettime;
	aicontroller->SetFocalPoint(targetpos, EAIFocusPriority::Move);
	EPathFollowingRequestResult::Type result = aicontroller->MoveToLocation(targetpos, 10.0f);
	if (result == EPathFollowingRequestResult::Failed)
	{
		FVector movedir = (targetpos- ship->GetActorLocation());
		movedir.Normalize();
		Target->AddMovementInput(movedir, 1.0f);
	}

	//WaitForMessage(OwnerComp, UBrainComponent::AIMessage_MoveFinished, result.MoveId);
	//WaitForMessage(OwnerComp, UBrainComponent::AIMessage_RepathFailed);
	//return EBTNodeResult::Succeeded;
	return EBTNodeResult::InProgress;
}
uint16 UBTTask_Aim::GetInstanceMemorySize() const {
	return sizeof(FBTAimApproachMemory);
}
void UBTTask_Aim::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	FBTAimApproachMemory *cache = (FBTAimApproachMemory *)(NodeMemory);
	FVector delta = cache->Target->GetActorLocation() - cache->SelfShip->GetActorLocation();
	float distance = delta.Size();
	if (distance<cache->ReorganizeRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	PredictionAndAim(distance,cache->Target, cache->SelfShip, cache->WeaponSpeed);
}
void UBTTask_Aim::PredictionAndAim(float distance, AShipPawnBase *Target, AShipPawnBase *SelfShip, float WeaponSpeed) const {
	float bullettime = distance / WeaponSpeed;
	FVector targetpos = Target->GetActorLocation() + Target->GetVelocity()*bullettime;
	AAIController *aicontroller = Cast<AAIController>(SelfShip->GetController());
	aicontroller->SetFocalPoint(targetpos, EAIFocusPriority::Move);
	EPathFollowingRequestResult::Type result = aicontroller->MoveToLocation(targetpos, 10.0f);
	if (result == EPathFollowingRequestResult::Failed)
	{
		FVector movedir = (targetpos - SelfShip->GetActorLocation());
		movedir.Normalize();
		Target->AddMovementInput(movedir, 1.0f);
	}
}