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
	GetCharacterMovement()->AirControl = 1000.0f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	isFacingRight = true;

	ActiveSeed = AVineSeed::StaticClass();

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAmeliaBlumeCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &AAmeliaBlumeCharacter::MoveRight);

	InputComponent->BindAction("Water", IE_Pressed, this, &AAmeliaBlumeCharacter::StartWater);
	InputComponent->BindAction("ThrowSeed", IE_Pressed, this, &AAmeliaBlumeCharacter::ThrowSeed);
	InputComponent->BindTouch(IE_Pressed, this, &AAmeliaBlumeCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AAmeliaBlumeCharacter::TouchStopped);


}

void AAmeliaBlumeCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
	// UE_LOG(LogTemp, Warning, TEXT("Facing right = %d"),isFacingRight);
	if (Value < 0)
		isFacingRight = false;
	else if (Value > 0)
		isFacingRight = true;
	else
		isFacingRight = isFacingRight;
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
	UE_LOG(LogTemp, Warning, TEXT("You pressed RT"));
	UWorld* const World = GetWorld();
	if (World)
	{
		// Set the spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		// Get a random location to spawn at
		FVector SpawnLocation = GetActorLocation();
		if (isFacingRight)
			SpawnLocation.Y = SpawnLocation.Y - 100;
		else
			SpawnLocation.Y = SpawnLocation.Y + 100;

		// Get a random rotation for the spawned item
		FRotator SpawnRotation;
		SpawnRotation.Yaw = FMath::FRand() * 360.f;
		SpawnRotation.Pitch = FMath::FRand() * 360.f;
		SpawnRotation.Roll = FMath::FRand() * 360.f;

		// spawn the pickup
		AWaterDrop* const SpawnedPickUp = World->SpawnActor<AWaterDrop>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}

void AAmeliaBlumeCharacter::ThrowSeed()
{
	UE_LOG(LogTemp, Warning, TEXT("You pressed LT"));
	UWorld* const World = GetWorld();
	if (World)
	{
		// Set the spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		// Get a location to spawn at
		FVector SpawnLocation = GetActorLocation();
		if (isFacingRight)
			SpawnLocation.Y = SpawnLocation.Y - 100;
		else
			SpawnLocation.Y = SpawnLocation.Y + 100;

		// Get a random rotation for the spawned item
		FRotator SpawnRotation;
		SpawnRotation.Yaw = FMath::FRand() * 360.f;
		SpawnRotation.Pitch = FMath::FRand() * 360.f;
		SpawnRotation.Roll = FMath::FRand() * 360.f;

		// spawn the seed
		ASeed* const SpawnedSeed = World->SpawnActor<ASeed>(ActiveSeed, SpawnLocation, SpawnRotation, SpawnParams);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}
