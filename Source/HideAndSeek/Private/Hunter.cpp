// Fill out your copyright notice in the Description page of Project Settings.


#include "Hunter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

// Sets default values
AHunter::AHunter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

// Called when the game starts or when spawned
void AHunter::BeginPlay()
{
    Super::BeginPlay();

    EnemyController = Cast<AAIController>(GetController());

    GetWorldTimerManager().SetTimer(HuntTimer, this, &AHunter::StartHunt, HuntDelay);
}

AActor* AHunter::PickRandomPatrolTarget()
{
    TArray<AActor*> ValidTargets;
    for (AActor* Target : PatrolTargets)
    {
        if (Target != PatrolTarget)
            ValidTargets.AddUnique(Target);
    }

    const int32 NumberOfPatrolTargets = ValidTargets.Num();
    if (NumberOfPatrolTargets > 0)
    {
        const int32 TargetSelection = FMath::RandRange(0, NumberOfPatrolTargets - 1);
        AActor* Target = ValidTargets[TargetSelection];
        return Target;
    }
    return nullptr;
}

void AHunter::MoveToTarget(AActor* Target)
{
    if (EnemyController && Target)
    {
        FAIMoveRequest MoveRequest;
        MoveRequest.SetGoalActor(Target);
        MoveRequest.SetAcceptanceRadius(15.f);
        EnemyController->MoveTo(MoveRequest);
    }
}

bool AHunter::HasReachedTarget(AActor* Target)
{
    if (Target)
    {
        const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
        return DistanceToTarget - PatrolRadius <= 0.001f;
    }
    return false;
}

void AHunter::StartHunt()
{
    PatrolTarget = PickRandomPatrolTarget();
    MoveToTarget(PatrolTarget);
}

// Called every frame
void AHunter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasReachedTarget(PatrolTarget))
    {
        AActor* Target = PickRandomPatrolTarget();
        PatrolTarget = Target;
        MoveToTarget(PatrolTarget);
    }
}

// Called to bind functionality to input
void AHunter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

