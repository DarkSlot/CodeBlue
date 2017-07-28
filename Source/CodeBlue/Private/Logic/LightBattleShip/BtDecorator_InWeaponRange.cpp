// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BtDecorator_InWeaponRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Ship/ShipPawnBase.h"
#include "AIController.h"


bool UBtDecorator_InWeaponRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent *component = OwnerComp.GetBlackboardComponent();
	AShipPawnBase *Target = Cast<AShipPawnBase>(component->GetValueAsObject("Target"));
	AShipPawnBase *ship = Cast<AShipPawnBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Target||!ship)
	{
		return false;
	}
	float WeaponRange = component->GetValueAsFloat("WeaponRange");

	FVector delta = Target->GetActorLocation() - ship->GetActorLocation();
	return delta.SizeSquared() < WeaponRange*WeaponRange;
}

