// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "Deer.h"
#include "AI_Deer_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ADeer::ADeer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	//set its controller class
	AIControllerClass = AAI_Deer_Controller::StaticClass();

	isCharging = false;
	isInChargeUp = false;

	//set up facing the proper direction, -1 for left, 1 for right
	faceDirection = -1;

	//this would lock it to the location in the editor but it's not working properly
	//lockedAxisValue = GetActorLocation().X;
	//This locks it to the current location of the plane axis
	lockedAxisValue = 1210.0;
}

void ADeer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// keeps isFacingRight updated
	FRotator deerRotation = GetActorRotation();
	if (deerRotation.Yaw > 80 && deerRotation.Yaw < 100)
		isFacingRight = false;
	else if (deerRotation.Yaw > -100 && deerRotation.Yaw < -80)
		isFacingRight = true;
	else
		isFacingRight = isFacingRight;
	
	if (!isCharging)
	{
		//simple AI movement
		MoveRight(faceDirection * 0.5);
		
	}
	else if (isCharging)
	{
		//AI that will slow down for warning, then suddenly charge
		if (isInChargeUp && chargeUpCooldown > 0)
		{
			chargeUpCooldown--;
			MoveRight(faceDirection *-1 * 0.3);
		}
		else
		{
			if (isInChargeUp)
				isInChargeUp = false;

			MoveRight(faceDirection * 1);
		}
	}

	//Simple Back & forth. If the velocity is ~0, it's collided and need to turn around
	if (!recentlyRotated && GetVelocity().Y <= 0.1 && GetVelocity().Y >= -0.1 && !isInChargeUp)
	{
		faceDirection *= -1;
		recentlyRotated = true;
		rotationCooldown = 60;
	}

	if (rotationCooldown > 0)
	{
		rotationCooldown--;
		FRotator quickRotate = GetActorRotation();
		quickRotate.Yaw += 3.0;
		SetActorRotation(quickRotate);
		isCharging = false;
		isInChargeUp = false;
	}
	else
		recentlyRotated = false;

	// Some code to keep character locked to a plane
	FVector currLoc = GetActorLocation();
	FVector newLoc = FVector(lockedAxisValue, currLoc.Y, currLoc.Z);
	SetActorLocation(newLoc);
}

void ADeer::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
	UE_LOG(LogTemp, Warning, TEXT("Deer Facing right = %d"), isFacingRight);
}