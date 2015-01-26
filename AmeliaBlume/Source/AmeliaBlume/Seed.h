// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Seed.generated.h"

/**
*
*/
UCLASS()
class AMELIABLUME_API ASeed : public AActor
{
	GENERATED_BODY()


protected:

	// the amount of water this seed has collected
	UPROPERTY(EditAnywhere)
		int32 WaterCount;

	// waterCount threshold. once reached, SproutPlant() will be called
	UPROPERTY(EditAnywhere)
		int32 HydrationGoal;

	// True if the seed is inside of soil object
	UPROPERTY(EditAnywhere)
		bool bIsPlanted;

	// This is the plant type that the seed will grow into
	/*UPROPERTY(EditAnywhere)
		TSubclassOf<class APlant> PlantType;*/

	// Destroys this ASeed object, and creates new APlant object.
	void SproutPlant();

public:
	
	// Constructor
	ASeed(const FObjectInitializer& ObjectInitializer);

	// returns current WaterCount
	int32 GetWaterCount();

	// returns HydrationGGoal
	int32 GetHydrationGoal();

	// returns bIsPlanted
	bool IsPlanted();

	// increments WaterCount. Checks to see if HydrationGoal was reached. If so, SproutPlant() is called.
	void CollectWater();



};
