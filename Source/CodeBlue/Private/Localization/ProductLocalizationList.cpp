// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ProductLocalizationList.h"

ProductLocalizationList *ProductLocalizationList::Instance = nullptr;
ProductLocalizationList::ProductLocalizationList()
{
	LocalList.Add(TEXT("Graphene"), NSLOCTEXT("Game", "Graphene", "Graphene"));
	LocalList.Add(TEXT("Food"), NSLOCTEXT("Game", "Food", "Food"));
}

ProductLocalizationList::~ProductLocalizationList()
{
}
void ProductLocalizationList::CreateLocalizationList() {
	Instance = new ProductLocalizationList();
}
FText ProductLocalizationList::FindProductName(const FString &name) {
	FText *result = Instance->LocalList.Find(name);
	if (result)
	{
		return *result;
	}
	return NSLOCTEXT("Game", "ErrorName", "ErrorName");
}
