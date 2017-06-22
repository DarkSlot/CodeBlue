// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "Buff.h"

Buff::Buff() {

}
Buff::~Buff() {

}
void Buff::SetActive(const bool active) {
	bActive = active;
}
bool Buff::IsActive() {
	return bActive;
}
void Buff::Tick(float DeltaTime) {
	BuffTimer += BuffDecay;
}

int32 Buff::GetLevel() {
	return BuffLevel;
}


