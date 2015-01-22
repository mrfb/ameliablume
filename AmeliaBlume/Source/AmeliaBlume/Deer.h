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

	//override default tick function
	virtual void Tick(float DeltaTime) OVERRIDE;
	
	
};
