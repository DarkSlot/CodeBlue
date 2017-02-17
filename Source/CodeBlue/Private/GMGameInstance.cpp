// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "GMGameInstance.h"
#include "Market/MarketProcessCore.h"


UGMGameInstance::UGMGameInstance() {
	ProductLocalizationList::CreateLocalizationList();
	MarketProcessCore::StartGetInstance();
}
UGMGameInstance::~UGMGameInstance() {
	MarketProcessCore::Shutdown();
}


