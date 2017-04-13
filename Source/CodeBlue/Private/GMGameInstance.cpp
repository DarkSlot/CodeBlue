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
void UGMGameInstance::CreateGameUI() {
	//static ConstructorHelpers::FClassFinder<UUserWidget> MainGameUIClass(TEXT("/Game/UI/Game/MainGameUI"));
	UObject* tAsset = LoadObject<UClass>(nullptr, TEXT("/Game/UI/Game/MainGameUI.MainGameUI_C"));
	if (!tAsset) return;
	UClass* bp = Cast<UClass>(tAsset);
	if (!bp) return;
	WidgetInstance = CreateWidget<UUserWidget>(this, bp);
	WidgetInstance->AddToViewport();
}


