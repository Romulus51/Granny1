// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Granny1GameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class GRANNY1_API AGranny1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		
	

public:
	UFUNCTION()
	void OnActorOutOfBounds(AMyCharacter* CharacterRef);
	UFUNCTION()
	void AddStrikes();
	UPROPERTY(BlueprintReadOnly)
	int32 Strikes = 0;

	UFUNCTION()
	void ResetCamera(float DeltaTime);
	AActor* Camera = nullptr;
	AMyCharacter* CharacterGMRef = nullptr;
	// UFUNCTION(BlueprintCallable)
	// void OnEventTick();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float CameraLagSpeed = 2.f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float WaitBeforePlay = 3.0f;
	FTimerHandle ReadyAtStartTimer;
	void AllowPlayerToMove();

};
