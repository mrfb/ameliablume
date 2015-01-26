// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "WaterDrop.h"
#include "Seed.h"
#include "VineSeed.h"
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

	UPROPERTY(EditAnywhere, Category = Spawning)
		TSubclassOf<class AWaterDrop> WhatToSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
		TSubclassOf<class ASeed> ActiveSeed;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ASeed>> Seeds;

	UPROPERTY(EditAnywhere)
		bool isFacingRight;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	void StartWater();

	void ThrowSeed();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	AAmeliaBlumeCharacter(const FObjectInitializer& ObjectInitializer);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
