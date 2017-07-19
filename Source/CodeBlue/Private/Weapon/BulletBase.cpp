// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BulletBase.h"


// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	if (BulletMovement)
	{
		BulletMovement->UpdatedComponent = GetRootComponent();
	}
	Damage = 10;

	//Start with collision disable
	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor!= Launcher)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, LauncherController, this, nullptr);
		Destroy();
	}
}
