// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "BuffStarving.h"

BuffStarving::BuffStarving() {
	BuffTimer = 0.0f;
	BuffDecay = 1.0f;
}
BuffStarving::~BuffStarving() {

}

void BuffStarving::Reset() {
	BuffTimer = 0.0f;
	BuffDecay = 1.0f;
	BuffLevel = 0;
}
void BuffStarving::Tick(float DeltaTime) {
	Buff::Tick(DeltaTime);
	if (BuffTimer > 20.0f)
	{
		BuffTimer -= 20.0f;
		BuffLevel++;
	}
}


