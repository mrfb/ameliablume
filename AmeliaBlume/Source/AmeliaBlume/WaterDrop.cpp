// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "WaterDrop.h"

AWaterDrop::AWaterDrop(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	canDestroy = false;
	destroyTimer = 2;
}


void AWaterDrop::DoSomething()
{
	//UE_LOG(LogTemp, Warning, TEXT("You Are Holding RT"));
}

void AWaterDrop::Tick(float DeltaSeconds)
{
	if (!canDestroy){
		destroyTimer++;
		if (destroyTimer > 70)
			canDestroy = true;
	}
	if (canDestroy){
		Destroy();
	}
}

void AWaterDrop::OnCollision()
{
	//canDestroy = true;
	//destroyTimer = GetWorld()->GetTimeSeconds();
}






