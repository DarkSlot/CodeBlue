// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MarketCommand.h"
/**
 * 
 */
class BuyProductInNeed : public MarketCommand
{
public:
	BuyProductInNeed(const int32 productid, const int32 num,
		const int32 userid, const int32 depotid,const bool limitprice,const float limit);
	virtual ~BuyProductInNeed();
	virtual void Execute() override;
private:
	int32 ProductId;
	int32 Num;
	int32 UserId;
	int32 DepotId;
	bool bLimitPrice;
	float PriceLimit;
};
