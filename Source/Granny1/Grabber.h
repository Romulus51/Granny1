// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRANNY1_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	
	UFUNCTION()
	void IsGrabbed();
	bool bGrabbed = false;
	bool bCanGrab = false;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:

	class UPhysicsHandleComponent* PhysicsHandle = nullptr;
	class UInputComponent* InputComponent = nullptr;
	class APlayerController* PlayerControllerRef;	
	void Grab();
	void Release();
	FHitResult HitResult;	//Fix Zero for FHitResult
	FVector ReturnLineTraceEnd();
	FVector ReturnGrabbedObjectLocation();
	float Distance = 0.f;
	

};
