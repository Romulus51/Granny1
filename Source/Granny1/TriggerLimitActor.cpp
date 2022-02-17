// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLimitActor.h"
#include "Components/BoxComponent.h"



// Sets default values
ATriggerLimitActor::ATriggerLimitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CubeLimit = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeLimit"));
	CubeLimit->SetupAttachment(Root);

	TriggerLimit = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerLimit"));
	TriggerLimit->SetupAttachment(CubeLimit);

}

// Called when the game starts or when spawned
void ATriggerLimitActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATriggerLimitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}