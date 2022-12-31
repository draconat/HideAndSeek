// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Runner.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class HIDEANDSEEK_API ARunner : public ACharacter
{
    GENERATED_BODY()

public:
    ARunner();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = Input)
    UInputMappingContext* InputContext;

    UPROPERTY(EditAnywhere, Category = Input)
    UInputAction* MoveAction;

    void Move(const FInputActionValue& Value);

private:
    UPROPERTY(VisibleAnywhere)
        USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere)
        UCameraComponent* ViewCamera;

};
