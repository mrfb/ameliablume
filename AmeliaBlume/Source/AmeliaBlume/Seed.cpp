// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "Seed.h"


ASeed::ASeed(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Initialize water variables
	WaterCount = 0;
	HydrationGoal = 25;

	// Seed is initially NOT planted
	bIsPlanted = false;

	// By default, every seed is a tree seed
	/*PlantType = ATree::StaticClass();*/

	UE_LOG(LogTemp, Warning, TEXT("Seed created."));
	UE_LOG(LogTemp, Warning, TEXT("Default HydrationGoal: %d."), HydrationGoal);


}

void ASeed::SproutPlant()
{
	// Create new APlant entity, specificcal the type stored in PlantType.

	// Destroy this ASeed entity. The plant will carry on its legacy.
	// Goodnight, sweet seed. You served Amelia well.
	this->Destroy();
}

int32 ASeed::GetWaterCount()
{
	return WaterCount;
}

int32 ASeed::GetHydrationGoal()
{
	return HydrationGoal;
}

bool ASeed::IsPlanted()
{
	return bIsPlanted;
}

void ASeed::CollectWater()
{
	// increment WaterCount
	WaterCount++;

	// check to see if we've collected enough water
	if (WaterCount >= HydrationGoal)
	{
		// if we've reached out goal, it's time to sprout!
		SproutPlant();
	}
}