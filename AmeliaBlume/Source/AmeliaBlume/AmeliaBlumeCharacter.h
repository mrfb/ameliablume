// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "WaterDrop.h"
#include "AmeliaBlumeCharacter.generated.h"


UCLASS(config=Game)
class AAmeliaBlumeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


	//Used to Spawn Water drops
	//Set inside the hero blueprint
	UPROPERTY(EditAnywhere, Category = Spawning)
		TSubclassOf<class AWaterDrop> WhatToSpawn;

	//True when Amelia is facing the right side of the world
	UPROPERTY(EditAnywhere)
		bool isFacingRight;

	//Used to prevent Water Spamming
	UPROPERTY(EditAnywhere)
		int32 waterCooldown;

	//using this to keep the character locked to the correct plane
	UPROPERTY(EditAnywhere)
		float lockedAxisValue;


protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	//Continuously spawn water drops while trigger is held
	void KeepWatering(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	//Spawns one water drop
	void StartWater();

	//Stop watering once trigger is released
	void StopWater();




	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	AAmeliaBlumeCharacter(const FObjectInitializer& ObjectInitializer);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	//Overrides the tick function so it's editable in the cpp
	virtual void Tick(float DeltaTime) override;
};
