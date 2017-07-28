// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ShipPawnBase.h"
#include "../Weapon/BulletBase.h"

// Sets default values
AShipPawnBase::AShipPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxSpeed = 1000.0f;
	Acceleration = 500.0f;
	Agility = 50.0f;
	bIsFiring = false;
	FireTimer = 0.0f;
	HitPoint = 100.0f;
	HitPointMax = 100.0f;

	ShipMovement = CreateDefaultSubobject<UShipMovementComponent>(TEXT("ShipMovement"));
	if (ShipMovement)
	{
		ShipMovement->UpdatedComponent = GetRootComponent();
	}
}

// Called when the game starts or when spawned
void AShipPawnBase::BeginPlay()
{
	Super::BeginPlay();
	ShipMovement->MaxSpeed = MaxSpeed;
	ShipMovement->Acceleration = Acceleration;
	ShipMovement->Deceleration = Acceleration *2.0f;
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
void AShipPawnBase::FaceRotation(FRotator NewControlRotation, float DeltaTime) {
	FRotator rot = GetActorRotation();
	if (rot.Equals(NewControlRotation))
	{
		return;
	}
	FQuat currentquat= GetActorRotation().Quaternion();
	FQuat targetquat = NewControlRotation.Quaternion();
	float max_angular_mov = Agility/180*3.1415926f * DeltaTime;
	float target_move_angular = currentquat.AngularDistance(targetquat);

	if (target_move_angular<= max_angular_mov)
	{
		SetActorRotation(NewControlRotation);
	}
	else
	{
		FQuat actualquat = FQuat::Slerp(currentquat, targetquat, max_angular_mov / target_move_angular);
		SetActorRotation(actualquat);
	}
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
bool AShipPawnBase::ChangeZoomView_Implementation(float ZoomValue) {
	return true;
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
	//Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HitPoint -= DamageAmount;
	if (OnHitpointChanged.IsBound()) {
		OnHitpointChanged.Broadcast(HitPoint,HitPointMax);
	}
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
	DestroyShip();
}
void AShipPawnBase::DestroyShip_Implementation() {
	Destroy();
}
