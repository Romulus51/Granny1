// Copyright Epic Games, Inc. All Rights Reserved.


#include "Granny1GameModeBase.h"
#include "SpawnBlockActor.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Engine/EngineBaseTypes.h"
#include "Math/UnrealMathUtility.h"



void AGranny1GameModeBase::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(ReadyAtStartTimer, this, &AGranny1GameModeBase::AllowPlayerToMove, WaitBeforePlay, false);
    CharacterGMRef = Cast<AMyCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyCharacter::StaticClass()));
}


void AGranny1GameModeBase::AllowPlayerToMove()
{
    CharacterGMRef = Cast<AMyCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyCharacter::StaticClass()));
    if (!CharacterGMRef) return;
    CharacterGMRef->bPlayerCanDoAction = true;
    CharacterGMRef->PlayerCanDoActionFunction();
}

void AGranny1GameModeBase::OnActorOutOfBounds(AMyCharacter* CharacterRef)
{
    AddStrikes();
    if (!CharacterGMRef) return;
    FVector Location = CharacterRef->LastKnownLocation;
    FRotator Rotation = FRotator::ZeroRotator;
    if (ActorToSpawn == nullptr) return;
    GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
    ResetCamera(0.f);
}

void AGranny1GameModeBase::AddStrikes()
{
    Strikes++;
}

void AGranny1GameModeBase::ResetCamera(float DeltaTime)
{
    if (Camera)
    {}
    else
    {
    Camera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());

    }
    if (!CharacterGMRef)
    {
        CharacterGMRef = Cast<AMyCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyCharacter::StaticClass()));
    }

    FVector CharacterLocation = CharacterGMRef->GetActorLocation();
    FVector NewCameraLocation = FVector (CharacterLocation.X - 200.f, CharacterLocation.Y, 880.f);
    FVector CurrentCameraLocation = Camera->GetActorLocation();
    CurrentCameraLocation = FMath::Lerp(CurrentCameraLocation, NewCameraLocation, DeltaTime * CameraLagSpeed);
    Camera->SetActorLocation(CurrentCameraLocation, false);
}

	// void AGranny1GameModeBase::OnEventTick()
    // {
    //     if (!CharacterGMRef) return;
    //     if (CharacterGMRef->ShouldUpdateCamera())
    //     {
    //         ResetCamera();
    //     }
    //     else
    //     {
    //         UE_LOG(LogTemp, Warning, TEXT("ALLOW PLAYER TO MOVE"));
    //     }
    // }