// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "VineSeed.h"

AVineSeed::AVineSeed(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Change PlantType from the default value to a vine plant
	/*PlantType = AVine::StaticClass();*/

	// Set HydrationGoal to reflect the VineSeed requirements
	HydrationGoal = 20;

	UE_LOG(LogTemp, Warning, TEXT("VineSeed created."));
	UE_LOG(LogTemp, Warning, TEXT("Vine HydrationGoal: %d."), HydrationGoal);
}


