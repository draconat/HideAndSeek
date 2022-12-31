// Fill out your copyright notice in the Description page of Project Settings.


#include "HideAndSeekOverlay.h"
#include "Components/TextBlock.h"

void UHideAndSeekOverlay::SetGamePhase(FText GamePhaseName)
{
    if (GamePhase)
    {
        GamePhase->SetText(GamePhaseName);
    }
}

void UHideAndSeekOverlay::SetElapsedTime(float ElapsedTimefloat)
{
    if (ElapsedTime)
    {
        const int32 Minutes = floor((ElapsedTimefloat / 60.f));
        const float Seconds = ElapsedTimefloat - (Minutes * 60.f);
        ElapsedTime->SetText(FText::FromString(FString::Printf(TEXT("%d:%2.3f"), Minutes, Seconds)));
    }
}
