// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Granny1GameModeBase.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Grabber.h"
#include "Math/UnrealMathUtility.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	// UPhysicsHandleComponent* Grabber = FindComponentByClass<UPhysicsHandleComponent>();
	// if(Grabber)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s exists through chara"), *Grabber->GetName());
	// }
	// else{
	// 	UE_LOG(LogTemp, Warning, TEXT("failed finding grabber"));
	// }
	// Cast<APlayerController>(GetController())->SetInputMode(FInputModeGameAndUI());
	GameModeRef = GetWorld()->GetAuthGameMode<AGranny1GameModeBase>();
	GrabberRef = FindComponentByClass<UGrabber>();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShowHUDTimer)
	{
		ModifyHUDTimer(DeltaTime);
	}
	if (ShouldUpdateCamera())
	{
		GameModeRef->ResetCamera(DeltaTime);
	}
	else
	{

	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyCharacter::PlayerCanDoActionFunction()
{
	if (!GrabberRef) return;
	GrabberRef->bCanGrab = bPlayerCanDoAction;
}

void AMyCharacter::AddStrike()
{
	if (GameModeRef != nullptr)
	{
		GameModeRef->AddStrikes();
	}
}

void AMyCharacter::ResetCharacter()
{
	SetActorLocation(LastKnownLocation);
	if (GameModeRef != nullptr)
	{
		GameModeRef->OnActorOutOfBounds(this);
	}
}

void AMyCharacter::ModifyHUDTimer(float DeltaTime)
{
	HUDTimer -= DeltaTime;
	if(HUDTimer <= 0.f)
	{
		bShowHUDTimer = false;
	}
}

void AMyCharacter::ResetTimer()
{
	HUDTimer = 3.f;
	bShowHUDTimer = true;
}

void AMyCharacter::NullTimer()
{
	HUDTimer = 0.f;
	bShowHUDTimer = false;
}

bool AMyCharacter::ShouldUpdateCamera()
{
	if (!GrabberRef) return false;
	if (FMath::IsNearlyEqual(GetOwner()->GetVelocity().X, 0.f,1.f) && FMath::IsNearlyEqual(GetOwner()->GetVelocity().Y, 0.f,1.f) && FMath::IsNearlyEqual(GetOwner()->GetVelocity().Z, 0.f,1.f)&& !GrabberRef->bGrabbed)
	{
		return true;
	}
	else
	{
		return false;
	}

}

// BUG LIST : CAMERA FOLLOWING ACTOR WHILE BEING GRABBED. ACTOR GOING THROUGH FLOOR/DISAPPEARING
// CANNOT GRAB ACTOR