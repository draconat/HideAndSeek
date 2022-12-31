// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "Hunter.generated.h"

class UPawnSensingComponent;

UCLASS()
class HIDEANDSEEK_API AHunter : public ACharacter
{
    GENERATED_BODY()

public:
    AHunter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY()
    class AAIController* EnemyController;

    UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
    AActor* PatrolTarget;

    UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
    TArray<AActor*> PatrolTargets;

    UPROPERTY(EditAnywhere)
    double PatrolRadius = 200.f;

    UPROPERTY(EditAnywhere, Category = "AI Behavior")
    float HuntDelay;

    UPROPERTY(VisibleAnywhere, Category = "AI Behavior")
    AActor* HuntTarget;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void PawnSeen(APawn* SeenPawn);

private:
    UPROPERTY(VisibleAnywhere)
    UPawnSensingComponent* PawnSensing;

    AActor* PickRandomPatrolTarget();
    void MoveToTarget(AActor* Target, float AcceptanceRadius);
    bool TargetIsInRange(AActor* Target, double Range);

    FTimerHandle HuntTimer;
    void StartHunt();

    UPROPERTY(EditAnywhere)
    double HuntRadius = 500.f;

    UPROPERTY(EditAnywhere)
    EHunterState HunterState = EHunterState::EHS_Patrolling;
};
