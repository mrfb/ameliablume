// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "Soil.h"
#include "WaterDrop.h"

ASoil::ASoil(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Soil Made"));
	hydrationLevel = 0;
}


/*
Tick is called every frame
Checks for collisions and adds to hydrationLevel if it collides with water
*/
void ASoil::Tick(float DeltaSeconds)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tick is called"));
	TArray<AActor*> CollectedActors;
	GetOverlappingActors(CollectedActors); //Create a list of all overlapping actors
	
	//Go through the list of collisions
	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Collision?!?"));
		AWaterDrop* const TestWater = Cast<AWaterDrop>(CollectedActors[i]); //Cast current collided actor into a water drop
		if (TestWater && !TestWater->IsPendingKill()) //Checks to see if actor is actually a water drop and is not waiting to be destroyed
		{
			UE_LOG(LogTemp, Warning, TEXT("WaterCollision!"));
			hydrationLevel++;
			TArray<UActorComponent*> components;
			TestWater->GetComponents(components); //Get Components of the collided water
			for (int32 j = 0; j < components.Num(); ++j)
			{
				USphereComponent* thisComp = Cast<USphereComponent>(components[j]); //Find the collision sphere on the water
				if (thisComp)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Sphere"));
					thisComp->DestroyComponent(); //Destroy the collision sphere to prevent hydrationLevel from continously increasing
				}
			}
			TestWater->OnCollision();
			//UE_LOG(LogTemp, Warning, TEXT("Hydration = %d"), hydrationLevel);
		}
	}
}



