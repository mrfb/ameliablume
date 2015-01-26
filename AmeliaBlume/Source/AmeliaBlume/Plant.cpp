// Fill out your copyright notice in the Description page of Project Settings.

#include "AmeliaBlume.h"
#include "Plant.h"



//in the future constructor should also take SeedType
APlant::APlant(const FObjectInitializer& ObjectInitializer, SeedType type)
	: Super(ObjectInitializer)
{

}

void createProceduralMesh();
void grow();
void restrain();


PlantState[] getStates();
void addState(PlantState);
bool isState(PlantState);
void removeState(PlantState);
