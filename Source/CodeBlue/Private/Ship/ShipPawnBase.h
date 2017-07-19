// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "AIShipMovementComponent.h"
#include "ShipPawnBase.generated.h"

UCLASS()
class CODEBLUE_API AShipPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	//<productid,num>
	typedef TMap<int32, int32> CargoMap;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = Ship)
		void StartFireWeapon();

	UFUNCTION(BlueprintCallable, Category = Ship)
		void StopFireWeapon();

	UFUNCTION(BlueprintCallable, Category = Ship)
		bool AddCargo(int32 productid,int32 num);

	UFUNCTION(BlueprintCallable, Category = Ship)
	virtual	bool ReduceCargo(int32 productid, int32 num);

	UFUNCTION(BlueprintCallable, Category = Ship)
		TMap<int32, int32> &GetCargo();
		
	/** The speed of this ship. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
	float Speed;

	/** The Agility of this ship. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
	float Agility;
	
	///** The Agility of this ship. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ship)
	//UAIShipMovementComponent *ShipMovement;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ship)
	bool bIsFiring;

	float FireTimer;

	float HitPoint;

	CargoMap Cargo;

	void FireWeapon();
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	void BeingDestroyed();
};
