// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BuyProductInNeed.h"

BuyProductInNeed::BuyProductInNeed(const int32 productid, const int32 num,
	const int32 userid, const int32 depotid, const bool limitprice, const float limit) :
	ProductId(productid),
	Num(num),
	UserId(userid),
	DepotId(depotid),
	bLimitPrice(limitprice),
	PriceLimit(limit)
{
}

BuyProductInNeed::~BuyProductInNeed()
{
}
void BuyProductInNeed::Execute() {

}
