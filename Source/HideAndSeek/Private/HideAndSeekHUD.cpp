// Fill out your copyright notice in the Description page of Project Settings.


#include "HideAndSeekHUD.h"
#include "HideAndSeekOverlay.h"

void AHideAndSeekHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ElapsedTime += DeltaTime;

    HideAndSeekOverlay->SetElapsedTime(ElapsedTime);

    if (HideAndSeekOverlay)
    {
        if (!GameIsWon && ElapsedTime >= EscapeGoal)
        {
            HideAndSeekOverlay->SetGamePhase(FText::FromString(TEXT("Congratulations! You've won!")));
            GameIsWon = true;
        }
        else if (!HuntHasStarted && ElapsedTime > HuntDelay)
        {
            HideAndSeekOverlay->SetGamePhase(FText::FromString(TEXT("Evade the hunters!")));
            HuntHasStarted = true;
        }
    }
}

void AHideAndSeekHUD::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (World)
    {
        APlayerController* Controller = World->GetFirstPlayerController();
        if (Controller && HideAndSeekOverlayClass)
        {
            HideAndSeekOverlay = CreateWidget<UHideAndSeekOverlay>(Controller, HideAndSeekOverlayClass);
            HideAndSeekOverlay->AddToViewport();

            HideAndSeekOverlay->SetGamePhase(FText::FromString(TEXT("Find a place to hide!")));
        }
    }
}
