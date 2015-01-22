// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Deer.generated.h"

/**
 * 
 */
UCLASS()
class AMELIABLUME_API ADeer : public ACharacter
{
	GENERATED_BODY()

	//saves the initial value of the axis rather than memorizing a hard number
	UPROPERTY(EditAnywhere)
		float lockedAxisValue;

	UPROPERTY(EditAnywhere)
		bool isFacingRight;
	
	UPROPERTY(EditAnywhere)
		int8 faceDirection;

	UPROPERTY(EditAnywhere)
		bool recentlyRotated;

	UPROPERTY(EditAnywhere)
		int32 rotationCooldown;

	//override default tick function
	virtual void Tick(float DeltaTime) OVERRIDE;
	virtual void MoveRight(float value);

public:
	ADeer(const FObjectInitializer& ObjectInitializer);
	
};
