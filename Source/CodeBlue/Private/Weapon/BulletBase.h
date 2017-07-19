// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

UCLASS()
class ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	AActor *Launcher;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	AController *LauncherController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	UProjectileMovementComponent *BulletMovement;
	
};
