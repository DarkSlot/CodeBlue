// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "ProduceCenter.h"
#include "../Data/DataProcesser.h"
#include "../Data/ProduceLineDataItem.h"

UProduceCenter::UProduceCenter():DataProcesser(nullptr) {
	
}

UProduceCenter::~UProduceCenter()
{
}
void UProduceCenter::Init(UDataProcesser *dataProcesser) {
	DataProcesser = dataProcesser;

	UDataTable *ProduceLineDataTable =
		LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/ProduceLineData.ProduceLineData"));

	static const FString ContextString(TEXT("GENERAL"));

	TArray<FProduceLineDataItem *> ProduceArray;
	ProduceLineDataTable->GetAllRows(ContextString, ProduceArray);
	for (auto row : ProduceArray)
	{
		AddProduceLine(row->UserId,row->StationId,row->ProductId);
	}
}
void UProduceCenter::Produce(float DeltaTime) {
	for (auto line: ProduceLineList)
	{
		line->Produce(DeltaTime);
	}
}
void UProduceCenter::AddProduceLine(int32 user, int32 station, int32 product) {
	TMap<int32, FProductInfoItem *> &InfoMap = DataProcesser->GetProductInfo();
	FProductInfoItem *infoitem = InfoMap[product];
	ProduceLineList.Add(new ProduceLine(DataProcesser, ProduceLineList.Num(),user,station,product, infoitem->BaseTime,infoitem->BaseProduction));
}
void UProduceCenter::RemoveProduceLine(int32 lineid) {
	int32 size = ProduceLineList.Num();
	for (int32 i = 0; i < size; i++)
	{
		ProduceLine *line = ProduceLineList[i];
		if (line->GetLineId() == lineid)
		{
			ProduceLineList.RemoveAt(i);
			break;
		}
	}
}
void UProduceCenter::FindProduceLineByUser(int32 user, TArray<ProduceLine *> &lines) {
	for (auto line: ProduceLineList)
	{
		if (line->GetUserId() == user)
		{
			lines.Add(line);
		}
	}
}
