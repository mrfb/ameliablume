// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "WaterDrop.h"

AWaterDrop::AWaterDrop(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PrimaryActorTick.bCanEverTick = true;
}


void AWaterDrop::DoSomething()
{
	UE_LOG(LogTemp, Warning, TEXT("You Are Holding RT"));
}

void AWaterDrop::Tick(float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("Tick is called"));
}






