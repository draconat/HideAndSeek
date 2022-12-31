#pragma once

UENUM(BlueprintType)
enum class ERunnerState : uint8
{
    ERS_Running UMETA(DisplayName = "Running"),
    ERS_Caught UMETA(DisplayName = "Caught")
};

UENUM(BlueprintType)
enum class EHunterState : uint8
{
    EHS_Patrolling UMETA(DisplayName = "Patrolling"),
    EHS_Chasing UMETA(DisplayName = "Chasing")
};