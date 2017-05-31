// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "StartUpGameMode.h"
#include "ShipPlayerController.h"


AStartUpGameMode::AStartUpGameMode() {
	// use our custom PlayerController class
	PlayerControllerClass = AShipPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}


