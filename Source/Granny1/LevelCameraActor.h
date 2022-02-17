// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "LevelCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class GRANNY1_API ALevelCameraActor : public ACameraActor
{
	GENERATED_BODY()
public:

	ALevelCameraActor();

private:
	// UPROPERTY(VisibleAnywhere)
	// USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
};
