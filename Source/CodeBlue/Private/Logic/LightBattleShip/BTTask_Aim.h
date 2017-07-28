// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTTask_Aim.generated.h"

class AShipPawnBase;
struct FBTAimApproachMemory
{
	AShipPawnBase *Target;
	AShipPawnBase *SelfShip;
	float WeaponSpeed;
	float ReorganizeRange;
};
/**
 * 
 */
UCLASS()
class UBTTask_Aim : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	/** size of instance memory */
	virtual uint16 GetInstanceMemorySize() const override;
protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	void PredictionAndAim(float distance,AShipPawnBase *Target,AShipPawnBase *SelfShip,float WeaponSpeed) const;
};
