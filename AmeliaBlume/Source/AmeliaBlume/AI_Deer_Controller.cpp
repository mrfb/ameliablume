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
	ADeer* Bot = Cast<ADeer>(InPawn);
	if (Bot && Bot->DeerBehavior)
	{
		BlackboardComp->InitializeBlackboard(*(Bot->DeerBehavior->BlackboardAsset));

		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");

		BehaviorComp->StartTree(*(Bot->DeerBehavior));
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

void AAI_Deer_Controller::checkIfPlayerSeen()
{

}

void AAI_Deer_Controller::chasePlayer()
{

}