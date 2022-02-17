// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBlockActor.h"

// Sets default values
ASpawnBlockActor::ASpawnBlockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	FrontMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontMesh"));
	FrontMesh->SetupAttachment(Root);

	BackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackMesh"));
	BackMesh->SetupAttachment(Root);

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightMesh"));
	RightMesh->SetupAttachment(Root);

	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftMesh"));
	LeftMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASpawnBlockActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialActorLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	CurrentActorLocation = InitialActorLocation;
	float FinalX = InitialActorLocation.X;
	float FinalY = InitialActorLocation.Y;
	float FinalZ = InitialActorLocation.Z - 500.f;
	FinalActorLocation = FVector (InitialActorLocation.X,InitialActorLocation.Y,InitialActorLocation.Z - 500.f);

	UE_LOG(LogTemp, Warning, TEXT("%s InitialActorLocation, %s FinalActorLocation"), *InitialActorLocation.ToString(), *FinalActorLocation.ToString());

}

// Called every frame
void ASpawnBlockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Countdown -= DeltaTime;

	if (Countdown < 0.f)
	{
		MoveSpawnBlockActor(DeltaTime);

		if(GetActorLocation() == FinalActorLocation)
		{
			Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Destroyed"));
		}
	}
	
}


void ASpawnBlockActor::MoveSpawnBlockActor( float DeltaTime)
{
	CurrentActorLocation = FMath::Lerp(CurrentActorLocation, FinalActorLocation, DeltaTime * 0.9f);

	Root->SetRelativeLocation(CurrentActorLocation, false);


}