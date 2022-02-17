// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerLimitActor.h"
#include "OutOfBoundsLimitActor.generated.h"

/**
 * 
 */
UCLASS()
class GRANNY1_API AOutOfBoundsLimitActor : public ATriggerLimitActor
{
	GENERATED_BODY()
	
public:
	bool bIsOverlapping = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void ActionWhenOverlap();
	void CheckTimer();
	FTimerHandle ResetPlayerTimer;

private:

	class AMyCharacter* MyCharacterRef = nullptr;
};
