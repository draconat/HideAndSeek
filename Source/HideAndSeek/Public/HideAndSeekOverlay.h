// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HideAndSeekOverlay.generated.h"

class UTextBlock;

UCLASS()
class HIDEANDSEEK_API UHideAndSeekOverlay : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetGamePhase(FText GamePhaseName);
    void SetElapsedTime(float ElapsedTimefloat);

private:
    UPROPERTY(meta = (BindWidget))
        UTextBlock* GamePhase;

    UPROPERTY(meta = (BindWidget))
        UTextBlock* ElapsedTime;
};
