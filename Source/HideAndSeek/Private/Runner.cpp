// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ARunner::ARunner()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->TargetArmLength = 5000.f;
    // Camera is ficed
    CameraBoom->SetAbsolute(false, true);
    CameraBoom->AddWorldRotation(FRotator(-45.f, -45.f, 0.f));

    ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
    ViewCamera->SetupAttachment(CameraBoom);
    ViewCamera->FieldOfView = 45.f;
}

void ARunner::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputContext, 0);
        }
    }
}

void ARunner::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller)
    {
        // Rotation Matrix uses rotation of the fixed camera
        const FRotator CameraRotation = CameraBoom->GetRelativeRotation();
        const FRotator YawRotation(0.f, CameraRotation.Yaw, 0.f);
        const FRotationMatrix RotationMatrix = FRotationMatrix(YawRotation);
        const FVector Direction = RotationMatrix.GetUnitAxis(EAxis::X);
        const FVector Right = RotationMatrix.GetUnitAxis(EAxis::Y);

        AddMovementInput(Direction, MovementVector.Y);
        AddMovementInput(Right, MovementVector.X);
    }
}

void ARunner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ARunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);


    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunner::Move);
    }
}

