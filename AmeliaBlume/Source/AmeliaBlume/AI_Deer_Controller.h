// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI_Deer_Controller.generated.h"

/**
 * 
 */
UCLASS()
class AMELIABLUME_API AAI_Deer_Controller : public AAIController
{
	GENERATED_BODY()

	//Define blackboard component (used to be a special TSubobjectptr call, now just normal pointers
	UPROPERTY(transient)
	UBlackboardComponent* BlackboardComp;

	//define the Behavior Tree component
	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY(transient)
		class ADeer* MyDeer;

	// horizontal distance player must be in in order to cause the deer to charge
	UPROPERTY(EditAnywhere)
		float chargeYDistance;

	// vertical range player must be in in order to cause the deer to charge
	UPROPERTY(EditAnywhere)
		float chargeZDistance;

	virtual void Possess(class APawn *InPawn);

	//behavior that checks if the deer sees the player
	UFUNCTION(BlueprintCallable, Category = Behavior)
	bool checkIfPlayerSeen();

	//behavior that makes deer idle
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void idle();

	//behavior that causes dee to chase player
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void chasePlayer();

	
protected:
	uint8 EnemyKeyID;
	uint8 EnemyLocationID;

public:
	AAI_Deer_Controller(const class FObjectInitializer& PCIP);
};
