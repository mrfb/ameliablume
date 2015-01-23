// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AI_Deer_Controller.generated.h"

/**
 * 
 */
UCLASS()
class AMELIABLUME_API AAI_Deer_Controller : public AAIController
{
	GENERATED_BODY()

	void checkIfPlayerSeen();


	void chasePlayer();
	
	
};
