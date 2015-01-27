// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "Soil.h"
#include "WaterDrop.h"

ASoil::ASoil(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Soil Made"));
	hydrationLevel = 0;
}

void ASoil::Tick(float DeltaSeconds)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tick is called"));
	TArray<AActor*> CollectedActors;
	GetOverlappingActors(CollectedActors);
	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision?!?"));
		AWaterDrop* const TestWater = Cast<AWaterDrop>(CollectedActors[i]);
		if (TestWater && !TestWater->IsPendingKill())
		{
			UE_LOG(LogTemp, Warning, TEXT("WaterCollision!"));
			hydrationLevel++;
			TArray<UActorComponent*> components;
			TestWater->GetComponents(components);
			for (int32 j = 0; j < components.Num(); ++j)
			{
				USphereComponent* thisComp = Cast<USphereComponent>(components[i]);
				if (thisComp)
				{
					UE_LOG(LogTemp, Warning, TEXT("Sphere"));
					thisComp->DestroyComponent();
				}
			}
			//TestWater->OnCollision();
			UE_LOG(LogTemp, Warning, TEXT("Hydration = %d"), hydrationLevel);
		}
	}
}



