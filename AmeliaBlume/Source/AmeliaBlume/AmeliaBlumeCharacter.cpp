// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "AmeliaBlume.h"
#include "AmeliaBlumeCharacter.h"


AAmeliaBlumeCharacter::AAmeliaBlumeCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	isFacingRight = true;
	waterCooldown = 1; //Water cooldown is 1 second because the particle system takes this long to cycle


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//this would lock it to the location in the editor but it's not working properly
	//lockedAxisValue = GetActorLocation().X;
	//This locks it to the current location of the plane axis
	lockedAxisValue = 1210.0;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAmeliaBlumeCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &AAmeliaBlumeCharacter::MoveRight);
	
	InputComponent->BindAxis("WaterHold", this, &AAmeliaBlumeCharacter::KeepWatering);


	//InputComponent->BindAction("Water", IE_Pressed, this, &AAmeliaBlumeCharacter::StartWater);
	//InputComponent->BindAction("Water", IE_Released, this, &AAmeliaBlumeCharacter::StopWater);

	InputComponent->BindTouch(IE_Pressed, this, &AAmeliaBlumeCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AAmeliaBlumeCharacter::TouchStopped);


}

void AAmeliaBlumeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//making sure the player stays on the correct plane
	FVector currLoc = GetActorLocation();
	FVector newLoc = FVector(lockedAxisValue, currLoc.Y, currLoc.Z);
	SetActorLocation(newLoc);
}

void AAmeliaBlumeCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
	//UE_LOG(LogTemp, Warning, TEXT("Facing right = %d"),isFacingRight);

	//Determine Amelia's direction based on the last direction she moved
	if (Value < 0)
		isFacingRight = false;
	else if (Value > 0)
		isFacingRight = true;
	else
		isFacingRight = isFacingRight;
}

void AAmeliaBlumeCharacter::KeepWatering(float Value)
{
	GetWorld()->GetTimeSeconds(); //Get amount of time passed in the game
	//UE_LOG(LogTemp, Warning, TEXT("%d"), waterCooldown);
	
	// Spawn water if trigger is held and at least one second has passed since the last spawned water
	if (Value > 0 && (GetWorld()->GetTimeSeconds() - waterCooldown) > 1) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Watering %d"), waterCooldown);
		waterCooldown = GetWorld()->GetTimeSeconds();
		StartWater();
	}
}

void AAmeliaBlumeCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AAmeliaBlumeCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AAmeliaBlumeCharacter::StartWater()
{
	//UE_LOG(LogTemp, Warning, TEXT("You pressed RT"));
	UWorld* const World = GetWorld(); 
	if (World) //Test to make sure world is valid
	{
		// Set the spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		// Get a random location to spawn at
		FVector SpawnLocation = GetActorLocation(); //Get location of Amelia
		if (isFacingRight)
			SpawnLocation.Y = SpawnLocation.Y - 100; //Spawn water in front of amelia by 100 units
		else
			SpawnLocation.Y = SpawnLocation.Y + 100;

		// Get a random rotation for the spawned item
		FRotator SpawnRotation; //Give each drop a random rotation 
		SpawnRotation.Yaw = FMath::FRand() * 360.f;
		SpawnRotation.Pitch = FMath::FRand() * 360.f;
		SpawnRotation.Roll = FMath::FRand() * 360.f;

		// spawn the water
		AWaterDrop* const water = World->SpawnActor<AWaterDrop>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams); //Actually spawns water

	}
}

void  AAmeliaBlumeCharacter::StopWater()
{
	//AWaterDrop* waterDrop = Cast<AWaterDrop>(WhatToSpawn);
	//waterDrop->DoSomething();
}

