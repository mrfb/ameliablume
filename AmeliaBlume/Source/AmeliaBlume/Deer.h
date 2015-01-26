// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Deer.generated.h"


/**
 * 
 */
UCLASS()
class AMELIABLUME_API ADeer : public ACharacter
{
	GENERATED_BODY()

public:
	ADeer(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* DeerBehavior;

	//saves the initial value of the axis rather than memorizing a hard number
	UPROPERTY(EditAnywhere)
		float lockedAxisValue;

	UPROPERTY(EditAnywhere)
		bool isFacingRight;

	UPROPERTY(EditAnywhere)
		bool isCharging;

	UPROPERTY(EditAnywhere)
		bool isInChargeUp;

	UPROPERTY(EditAnywhere)
		int32 chargeUpCooldown;

	UPROPERTY(EditAnywhere)
		bool recentlyRotated;


	//override default tick function
	virtual void Tick(float DeltaTime) override;
	virtual void MoveRight(float value);

private:
	UPROPERTY(EditAnywhere)
		int8 faceDirection;

	UPROPERTY(EditAnywhere)
		int32 rotationCooldown;
	
};
