// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    // UUserWidget* HUDScreen = CreateWidget(this, HUDClass);
    // if (HUDScreen != nullptr)
    // {
    //     HUDScreen->AddToViewport();
    // }

    FInputModeGameAndUI inputMode;
    inputMode.SetHideCursorDuringCapture(false);
    SetInputMode(inputMode);
    UE_LOG(LogTemp, Warning, TEXT("Starts PC"));
    
}