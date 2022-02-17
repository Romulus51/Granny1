// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerLimitActor.generated.h"

UCLASS()
class GRANNY1_API ATriggerLimitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerLimitActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerLimit;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeLimit;



	
};
