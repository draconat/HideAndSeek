// Fill out your copyright notice in the Description page of Project Settings.


#include "Hunter.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AHunter::AHunter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->MaxWalkSpeed = 300.f;

    PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
    PawnSensing->bHearNoises = false;
    PawnSensing->SightRadius = 5000.f;
    PawnSensing->SetPeripheralVisionAngle(45.f);
}

// Called when the game starts or when spawned
void AHunter::BeginPlay()
{
    Super::BeginPlay();

    EnemyController = Cast<AAIController>(GetController());

    GetWorldTimerManager().SetTimer(HuntTimer, this, &AHunter::StartHunt, HuntDelay);
    
    Tags.Add(FName("Hunter"));

    if (PawnSensing)
        PawnSensing->OnSeePawn.AddDynamic(this, &AHunter::PawnSeen);
}

void AHunter::PawnSeen(APawn* SeenPawn)
{
    if (HunterState == EHunterState::EHS_Chasing) return;

    if (SeenPawn->ActorHasTag(FName("Runner")))
    {
        HunterState = EHunterState::EHS_Chasing;
        GetCharacterMovement()->MaxWalkSpeed = 600.f;
        HuntTarget = SeenPawn;
        MoveToTarget(HuntTarget, 0.1f);
    }
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

void AHunter::MoveToTarget(AActor* Target, float AcceptanceRadius)
{
    if (EnemyController && Target)
    {
        FAIMoveRequest MoveRequest;
        MoveRequest.SetGoalActor(Target);
        MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
        EnemyController->MoveTo(MoveRequest);
    }
}

bool AHunter::TargetIsInRange(AActor* Target, double Range)
{
    if (Target)
    {
        const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
        return DistanceToTarget - Range <= 0.001f;
    }
    return false;
}

void AHunter::StartHunt()
{
    PatrolTarget = PickRandomPatrolTarget();
    MoveToTarget(PatrolTarget, 15.f);
}

// Called every frame
void AHunter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HunterState == EHunterState::EHS_Chasing && !TargetIsInRange(HuntTarget, HuntRadius))
    {
        HunterState = EHunterState::EHS_Patrolling;
        GetCharacterMovement()->MaxWalkSpeed = 300.f;
    }

    if (HunterState == EHunterState::EHS_Patrolling && TargetIsInRange(PatrolTarget, PatrolRadius))
    {
        AActor* Target = PickRandomPatrolTarget();
        PatrolTarget = Target;
        MoveToTarget(PatrolTarget, 15.f);
    }
}

// Called to bind functionality to input
void AHunter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

