// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Soil.generated.h"

/**
 * 
 */
UCLASS()
class AMELIABLUME_API ASoil : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) OVERRIDE;

	ASoil(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
		int32 hydrationLevel;
	
	
	
};
