// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HideAndSeekHUD.generated.h"

class UHideAndSeekOverlay;

UCLASS()
class HIDEANDSEEK_API AHideAndSeekHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void Tick(float DeltaTime) override;

    FORCEINLINE UHideAndSeekOverlay* GetHideAndSeekOverlay() const { return HideAndSeekOverlay; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Hide and Seek")
    TSubclassOf<UHideAndSeekOverlay> HideAndSeekOverlayClass;

    UPROPERTY()
    UHideAndSeekOverlay* HideAndSeekOverlay;

    float ElapsedTime = 0.f;
    float HuntDelay = 30.f; // Hunters start after 30 seconds
    float EscapeGoal = 300.f; // Game is won after 5 minutes
    bool HuntHasStarted = false;
    bool GameIsWon = false;
};
