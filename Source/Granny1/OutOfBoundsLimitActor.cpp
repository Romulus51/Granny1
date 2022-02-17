// Fill out your copyright notice in the Description page of Project Settings.


#include "OutOfBoundsLimitActor.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Grabber.h"

void AOutOfBoundsLimitActor::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerLimit->OnComponentBeginOverlap.AddDynamic(this, &AOutOfBoundsLimitActor::OnBoxBeginOverlap);
	TriggerLimit->OnComponentEndOverlap.AddDynamic(this, &AOutOfBoundsLimitActor::OnBoxEndOverlap);

}

void AOutOfBoundsLimitActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MyCharacterRef = Cast<AMyCharacter>(OtherActor);
	
    UE_LOG(LogTemp, Warning, TEXT("Reset actor location"));
	ActionWhenOverlap();
}

void AOutOfBoundsLimitActor::ActionWhenOverlap()
{
    if (MyCharacterRef)
	{
		bIsOverlapping = true;
		UGrabber* GrabberRef = MyCharacterRef->FindComponentByClass<UGrabber>();
			if(GrabberRef)
			{
				if(GrabberRef->bGrabbed)
				{
				    GrabberRef->IsGrabbed();
				}
			GetWorldTimerManager().SetTimer(ResetPlayerTimer, this, &AOutOfBoundsLimitActor::CheckTimer, 3.f, false);
			MyCharacterRef->ResetTimer();
			}
	}
}

void AOutOfBoundsLimitActor::OnBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsOverlapping = false;
	GetWorldTimerManager().ClearTimer(ResetPlayerTimer);
	if (!MyCharacterRef) return;
	MyCharacterRef->NullTimer();
}

void AOutOfBoundsLimitActor::CheckTimer()
{
	if (MyCharacterRef && bIsOverlapping)
	{
		MyCharacterRef->ResetCharacter();
	}
}