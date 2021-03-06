// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "AmeliaBlume.h"
#include "AmeliaBlumeGameMode.h"
#include "AmeliaBlumeCharacter.h"

AAmeliaBlumeGameMode::AAmeliaBlumeGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
