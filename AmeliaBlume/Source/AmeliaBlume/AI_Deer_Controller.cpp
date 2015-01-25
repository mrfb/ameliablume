// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "AI_Deer_Controller.h"
#include "Deer.h"
#include "AmeliaBlumeCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

//contstructor
AAI_Deer_Controller::AAI_Deer_Controller(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
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

void AAI_Deer_Controller::SearchForEnemy()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
		return;

	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	AAmeliaBlumeCharacter* BestPawn = NULL;

	//iterates through all possible characters to chase, then picks the closest one
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		AAmeliaBlumeCharacter* TestPawn = Cast<AAmeliaBlumeCharacter>(*It);
		if (TestPawn)
		{
			const float DistSq = FVector::Dist(TestPawn->GetActorLocation(), MyLoc);
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPawn = TestPawn;
			}
		}
	}

	if (BestPawn)
	{
		SetEnemy(BestPawn);
	}
}

void AAI_Deer_Controller::SetEnemy(class APawn *InPawn)
{
	BlackboardComp->SetValueAsObject(EnemyKeyID, InPawn);
	BlackboardComp->SetValueAsVector(EnemyLocationID, InPawn->GetActorLocation());
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

	//get rotation of deer to tell what direction it's facing
	FRotator deerRotation = MyDeer->GetActorRotation();

	if (botLoc.Y - playerLoc.Y < 0 && !(deerRotation.Yaw > 80 && deerRotation.Yaw < 100) )
	{
		return true;
		MyDeer->isCharging = true;
	}
	else if (botLoc.Y - playerLoc.Y > 0 && (deerRotation.Yaw > -100 && deerRotation.Yaw < -80))
	{
		return true;
		MyDeer->isCharging = true;
	}

	return false;
}

void AAI_Deer_Controller::idle()
{

	//forget the player for now, we've stopped chasing
	BlackboardComp->ClearValue(EnemyKeyID);
	BlackboardComp->ClearValue(EnemyLocationID);

	MyDeer->isCharging = false;


}

void AAI_Deer_Controller::chasePlayer()
{

}