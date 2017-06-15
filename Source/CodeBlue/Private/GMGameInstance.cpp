// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "GMGameInstance.h"
#include "Market/MarketProcessCore.h"
#include "HAL/FileManager.h"


UGMGameInstance::UGMGameInstance():
	ProduceCenter(nullptr),
	AILogicManager(nullptr){
	ProductLocalizationList::CreateLocalizationList();
	//MarketProcessCore::StartGetInstance();
}
UGMGameInstance::~UGMGameInstance() {
	//MarketProcessCore::Shutdown();
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
void UGMGameInstance::CreateNewGameData() {
	DataProcesser = NewObject<UDataProcesser>();
	DataProcesser->Init();
	FUserDataItem item;
	item.username = TEXT("Inf");
	item.usertype = 0;
	item.money = 50000.0f;
	item.description = TEXT("");
	item.AIType = 0;
	MainUserId = DataProcesser->CreateNewUser(item);
	ProduceCenter = NewObject<UProduceCenter>();
	ProduceCenter->Init(DataProcesser);
	AILogicManager = NewObject<UAILogicManager>();
	AILogicManager->Init(this);
}
void UGMGameInstance::LoadGameDatabase() {

}

void UGMGameInstance::Tick(float DeltaTime) {
	if (ProduceCenter)
	{
		ProduceCenter->Produce(DeltaTime);
	}
	if (AILogicManager)
	{
		AILogicManager->ProcessLogicUnits(DeltaTime);
	}
}

