// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class GRANNY1_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	FVector LastKnownLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

 	void ResetCharacter();

	void AddStrike();

	UPROPERTY(BlueprintReadOnly)
	float HUDTimer = 3.f;
	UPROPERTY(BlueprintReadOnly)
	bool bShowHUDTimer = true;
	void ModifyHUDTimer(float DeltaTime);
	void ResetTimer();
	void NullTimer();
	bool bPlayerCanDoAction = false;
	void PlayerCanDoActionFunction();
	bool ShouldUpdateCamera();

private:
	class AGranny1GameModeBase* GameModeRef = nullptr;
	class UGrabber* GrabberRef = nullptr;
};
