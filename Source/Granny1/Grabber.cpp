// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "MyCharacter.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle) return;

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent)
	{
		InputComponent->BindAction("Grab",IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab",IE_Released, this, &UGrabber::Release);
	}

	PlayerControllerRef = Cast<APlayerController>(GetOwner()->GetInstigatorController());
	if (!PlayerControllerRef) return;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerControllerRef)
	{
		
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult);
		
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	}
	if (!PhysicsHandle) {return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		// Get Mouse Location & Direction
		FVector WorldLocation;
		FVector WorldDirection;
		PlayerControllerRef->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		
		// Set Object Physics Handle Location
		FVector NewLocation = WorldLocation + (WorldDirection * (HitResult.Distance - 250.f));
		PhysicsHandle->SetTargetLocation(NewLocation);
	}
}

FVector UGrabber::ReturnGrabbedObjectLocation()
{
	FVector WorldLocation;
	FVector WorldDirection;
	
	PlayerControllerRef->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	return WorldLocation + (WorldDirection * Distance);
}

FVector UGrabber::ReturnLineTraceEnd()
{
	FVector WorldLocation;
	FVector WorldDirection;
	
	PlayerControllerRef->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	
	PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult);
	// Distance = HitResult.Distance ;
	return (WorldLocation + (WorldDirection * 1000.f));
	
	// PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	// return HitResult.ImpactPoint;
	
}

void UGrabber::Grab()
{
	if (!bCanGrab) return;
	//Get CameraLocation
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	// Perform LineTrace to access 
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerViewPointLocation, ReturnLineTraceEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn));


		Distance = Hit.Distance - 200.f;
		
		UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
		if(Hit.GetActor())
		{
			// Check if character is not moving
			if (Hit.GetActor()->GetVelocity() == FVector (0.f,0.f,0.f))
			{
				AMyCharacter* MyCharacterRef = Cast<AMyCharacter>(GetOwner());
				MyCharacterRef->LastKnownLocation = Hit.GetActor()->GetActorLocation();
				UE_LOG(LogTemp, Warning, TEXT("ShowText : %s"), *MyCharacterRef->LastKnownLocation.ToString());
				Hit.GetComponent()->SetSimulatePhysics(true);
				PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, Hit.Location, FRotator (10.f,0.f,0.f));
				bGrabbed = true;
				// PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, Hit.Location);
			}

	}
}

void UGrabber::Release()
{
	if (!bCanGrab) return;
	// //Get CameraLocation
	// FVector PlayerViewPointLocation;
	// FRotator PlayerViewPointRotation;

	// GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	// // Perform LineTrace to access 
	// FHitResult Hit;
	
	// GetWorld()->LineTraceSingleByObjectType(Hit, PlayerViewPointLocation, ReturnLineTraceEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn));
	
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetName());

	AMyCharacter* MyCharacterRef = Cast<AMyCharacter>(GetOwner());
	
	if (PhysicsHandle->GetGrabbedComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("ReleaseRef works"));
		// MyCharacterRef->SetSimulatePhysicsWithDelay();
		PhysicsHandle->GetGrabbedComponent()->SetSimulatePhysics(true);
		PhysicsHandle->ReleaseComponent();
		bGrabbed = false;
		MyCharacterRef->AddStrike();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ReleaseRef DID NOT WORK"));
	}

}

void UGrabber::IsGrabbed()
{
	if (bGrabbed)
	{
		Release();
	}
}