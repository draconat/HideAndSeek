// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hunter.generated.h"

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

protected:
    virtual void BeginPlay() override;

private:
    AActor* PickRandomPatrolTarget();
    void MoveToTarget(AActor* Target);
    bool HasReachedTarget(AActor* Target);

    FTimerHandle HuntTimer;
    void StartHunt();
};
