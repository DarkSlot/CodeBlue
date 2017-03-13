// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "CodeBlueGameModeBase.h"
#include "Private/ShipPlayerController.h"

ACodeBlueGameModeBase::ACodeBlueGameModeBase() {
	// use our custom PlayerController class
	PlayerControllerClass = AShipPlayerController::StaticClass();

	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}



