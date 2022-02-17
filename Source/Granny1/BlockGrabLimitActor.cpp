// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockGrabLimitActor.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"
#include "Grabber.h"


void ABlockGrabLimitActor::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerLimit->OnComponentBeginOverlap.AddDynamic(this, &ABlockGrabLimitActor::OnBoxBeginOverlap);
	TriggerLimit->OnComponentEndOverlap.AddDynamic(this, &ABlockGrabLimitActor::OnBoxEndOverlap);

}

void ABlockGrabLimitActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* MyCharacterRef = Cast<AMyCharacter>(OtherActor);
	
	ActionWhenOverlap(MyCharacterRef);
}

void ABlockGrabLimitActor::ActionWhenOverlap(AMyCharacter* MyCharacterRef)
{

    UE_LOG(LogTemp, Warning, TEXT("child"));

    if (MyCharacterRef)
	{
		UGrabber* GrabberRef = MyCharacterRef->FindComponentByClass<UGrabber>();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GrabberRef->GetName());
			if(GrabberRef)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found Grabber"));
				if(GrabberRef->bGrabbed)
				{
				    GrabberRef->IsGrabbed();
				    UE_LOG(LogTemp, Warning, TEXT("Release Grabber"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("FAILED Release Grabber"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed finding Grabber"));
			}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ref did not work"));
	}
}

void ABlockGrabLimitActor::OnBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Destroy();

}