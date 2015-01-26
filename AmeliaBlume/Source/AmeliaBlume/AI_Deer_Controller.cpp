// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "AI_Deer_Controller.h"
#include "Deer.h"
#include "AmeliaBlumeCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine.h"

//contstructor
AAI_Deer_Controller::AAI_Deer_Controller(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	//set our seeing distance values
	chargeYDistance = 800.0;
	chargeZDistance = 400.0;
}

void AAI_Deer_Controller::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	MyDeer = Cast<ADeer>(InPawn);
	if (MyDeer && MyDeer->DeerBehavior)
	{
		BlackboardComp->InitializeBlackboard(*(MyDeer->DeerBehavior->BlackboardAsset));

		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");

		BehaviorComp->StartTree(*(MyDeer->DeerBehavior));
	}
}


//True if Deer is facing player and player is within a certain distance
bool AAI_Deer_Controller::checkIfPlayerSeen()
{

	//get the player character
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (player == NULL)
		return false;

	//assign location vector for easier access
	FVector botLoc = MyDeer->GetActorLocation();
	FVector playerLoc = player->GetActorLocation();

	float yDistance = abs(botLoc.Y - playerLoc.Y);
	float zDistance = abs(botLoc.Z - playerLoc.Z);


	// Check to see if player is in the seeing range
	if (yDistance <= chargeYDistance && zDistance <= chargeZDistance)
	{

		//check if deer is facing the right way to see the player
		if (botLoc.Y - playerLoc.Y < 0 && !(MyDeer->isFacingRight))
		{
			chasePlayer();
			return true;
		}
		else if (botLoc.Y - playerLoc.Y > 0 && MyDeer->isFacingRight)
		{
			chasePlayer();
			return true;
		}
	}

	return false;
}

void AAI_Deer_Controller::idle()
{
	//if we need to do anything special for idle, this is where it would be done
}

void AAI_Deer_Controller::chasePlayer()
{
	//make sure the deer is not already charging
	if (!(MyDeer->isCharging) && !(MyDeer->recentlyRotated))
	{
		MyDeer->isCharging = true;
		MyDeer->isInChargeUp = true;
		MyDeer->chargeUpCooldown = 60;
	}
}