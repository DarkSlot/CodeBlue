// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ShipPawnBase.h"
#include "../Weapon/BulletBase.h"

// Sets default values
AShipPawnBase::AShipPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 100.0f;
	Agility = 50.0f;
	bIsFiring = false;
	FireTimer = 0.0f;
	HitPoint = 100.0f;

	//ShipMovement = CreateDefaultSubobject<UAIShipMovementComponent>(TEXT("ShipMovement"));
	//if (ShipMovement)
	//{
	//	ShipMovement->UpdatedComponent = GetRootComponent();
	//}
}

// Called when the game starts or when spawned
void AShipPawnBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShipPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsFiring)
	{
		FireTimer += DeltaTime;
		if (FireTimer>0.5f)
		{
			FireTimer -= 0.5f;
			FireWeapon();
		}
	}
}

// Called to bind functionality to input
void AShipPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AShipPawnBase::StartFireWeapon() {
	bIsFiring = true;
	FireTimer = 0.0f;
}
void AShipPawnBase::StopFireWeapon() {
	bIsFiring = false;
	FireTimer = 0.0f;
}
bool AShipPawnBase::AddCargo(int32 productid, int32 num) {
	if (Cargo.Find(productid))
	{
		Cargo[productid] += num;
	}
	else
	{
		Cargo.Add(productid, num);
	}
	return true;
}
bool AShipPawnBase::ReduceCargo(int32 productid, int32 num) {
	if (Cargo.Find(productid))
	{
		if (Cargo[productid]> num)
		{
			Cargo[productid] -= num;
			return true;
		}
		else if (Cargo[productid] == num)
		{
			Cargo.Remove(productid);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
AShipPawnBase::CargoMap &AShipPawnBase::GetCargo() {
	return Cargo;
}
void AShipPawnBase::FireWeapon() {
	UObject* tAsset = LoadObject<UClass>(nullptr, TEXT("/Game/Weapons/Blueprint/Bullet.Bullet_C"));
	if (!tAsset) return;
	UClass* bp = Cast<UClass>(tAsset);
	FActorSpawnParameters parameter;
	parameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform trans = GetActorTransform();
	ABulletBase *bullet = Cast<ABulletBase>(GetWorld()->SpawnActor(bp, &trans, parameter));
	if (bullet)
	{
		bullet->Launcher = this;
		bullet->LauncherController = GetController();
		bullet->BulletMovement->Velocity = trans.GetRotation().GetForwardVector() * 2000.0f;
		bullet->SetActorEnableCollision(true);
	}
}
float AShipPawnBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser) {
	HitPoint -= DamageAmount;
	if (HitPoint<=0.0f)
	{
		BeingDestroyed();
	}
	return DamageAmount;
}
void AShipPawnBase::BeingDestroyed() {
	UParticleSystem* PSAsset = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/Environment/particles/Explosion_2.Explosion_2'"));
	if (!PSAsset) return;
	UClass* Wreck = LoadObject<UClass>(nullptr, TEXT("/Game/Ships/Wreck/WreckActor.WreckActor_C"));
	if (!Wreck) return;

	FActorSpawnParameters parameter;
	parameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform trans = GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PSAsset, trans, true);
	AShipPawnBase *wreck = Cast<AShipPawnBase>(GetWorld()->SpawnActor(Wreck, &trans, parameter));
	for (auto &item:Cargo)
	{
		wreck->AddCargo(item.Key, item.Value);
	}
	//ABulletBase *bullet = Cast<ABulletBase>(GetWorld()->SpawnActor(bp, &trans, parameter));

	Destroy();
}
