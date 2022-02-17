// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBlockActor.generated.h"

UCLASS()
class GRANNY1_API ASpawnBlockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnBlockActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RemoveBlockActor(float DeltaTime);
	void MoveSpawnBlockActor(float DeltaTime);

	FVector InitialActorLocation;
	FVector CurrentActorLocation;
	FVector FinalActorLocation;
	float Countdown = 2.f;
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrontMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BackMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeftMesh;



};
