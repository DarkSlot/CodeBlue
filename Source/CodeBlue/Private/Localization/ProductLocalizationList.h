// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Core.h"
/**
 * 
 */
class ProductLocalizationList
{
public:
	~ProductLocalizationList();

	static void CreateLocalizationList();
	static FText FindProductName(const FString &name);
private:
	static ProductLocalizationList *Instance;
	TMap<FString, FText> LocalList;

	ProductLocalizationList();
};
