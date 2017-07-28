// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ShipMovementComponent.h"
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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHitpointChanged, const float, hitpoint, const float, hitpointmax);

	//<productid,num>
	typedef TMap<int32, int32> CargoMap;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void FaceRotation(FRotator NewControlRotation, float DeltaTime = 0.f) override;


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
	
	UFUNCTION(BlueprintNativeEvent, Category = Ship)
	bool ChangeZoomView(float ZoomValue);
		
	/** The speed of this ship. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
	float MaxSpeed;

	/** The Agility of this ship. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
		float Acceleration;

	/** The Agility of this ship. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
	float Agility;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Ship)
	float HitPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ship)
	float HitPointMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ship)
	UShipMovementComponent *ShipMovement;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Data")
	FOnHitpointChanged OnHitpointChanged;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ship)
	bool bIsFiring;

	float FireTimer;


	CargoMap Cargo;

	void FireWeapon();
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	void BeingDestroyed();

	UFUNCTION(BlueprintNativeEvent, Category = Ship)
	void DestroyShip();

};
