// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "ProduceLine.h"
#include "ProduceCenter.generated.h"
/**
 * 
 */
class UDataProcesser; 
UCLASS()
class UProduceCenter : public UObject
{
	GENERATED_BODY()
public:
	UProduceCenter();
	~UProduceCenter();
	void Init(UDataProcesser *dataProcesser);

	void Produce(float DeltaTime);

	void AddProduceLine(int32 user, int32 station, int32 product);
	void RemoveProduceLine(int32 lineid);
private:
	TArray<ProduceLine *> ProduceLineList;
	UDataProcesser *DataProcesser;
};
