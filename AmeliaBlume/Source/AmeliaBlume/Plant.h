// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Plant.generated.h"

/**
 * 
 */
UCLASS()
class AMELIABLUME_API APlant : public APawn
{
	GENERATED_BODY()

	int hydration;
	int maturity;
	PlantState[] state;

protected:
	void CreateProceduralMesh();
	void Grow();
	void Restrain();

public:
	PlantState[] GetStates();
	void AddState(PlantState state);
	bool IsState(PlantState state);
	void RemoveState(PlantState state);
	
	
};
