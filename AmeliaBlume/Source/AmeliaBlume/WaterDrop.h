// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WaterDrop.generated.h"

/**
 * 
 */
UCLASS()
class AMELIABLUME_API AWaterDrop : public AActor
{
	GENERATED_BODY()

protected:
	//true if particles are done cycling
	bool canDestroy;

	//Used to delay the destroy to make sure particles finish
	int32 destroyTimer;

public:

	//Used for testing
	void DoSomething();

	//Destroy the water when it collides with another object
	void OnCollision();

	virtual void Tick(float DeltaSeconds) OVERRIDE;

	AWaterDrop(const FObjectInitializer& ObjectInitializer);
	
};
