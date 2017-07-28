// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "CodeBlueGameModeBase.h"
#include "Private/Ship/ShipPlayerController.h"

ACodeBlueGameModeBase::ACodeBlueGameModeBase() {
	// use our custom PlayerController class
	PlayerControllerClass = AShipPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	DefaultPawnClass = nullptr;
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Ships/BaseShip/BaseShip"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}



