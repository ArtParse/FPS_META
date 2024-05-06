#include "FPSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Weapons/Weapon.h"

AFPSPlayerController::AFPSPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  MoveInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Move.IA_Move'"));
  LookInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Look.IA_Look'"));
  JumpInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Jump.IA_Jump'"));
  AttackInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Attack.IA_Attack'"));
  ZoomInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Zoom.IA_Zoom'"));

  
  DefaultInputContext = LoadObject<UInputMappingContext>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputMappingContext'/Game/FPBody/Inputs/IMC_DefaultPlayer.IMC_DefaultPlayer'"));
}

void AFPSPlayerController::SetupInputComponent()
{
  Super::SetupInputComponent();

  UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
  UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

  check(PlayerEnhancedInputComponent != nullptr);
  check(Subsystem != nullptr);

  Subsystem->ClearAllMappings();
  Subsystem->AddMappingContext(DefaultInputContext, 0);

  if (MoveInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::Move);
  }

  if (LookInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::Look);
  }

  if (JumpInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::StartJump);
    PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &AFPSPlayerController::StopJump);
  }

  if (AttackInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(AttackInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::StartAttack);
    PlayerEnhancedInputComponent->BindAction(AttackInputAction, ETriggerEvent::Completed, this, &AFPSPlayerController::StopAttack);
  }
  
  if (ZoomInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(ZoomInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::StartZoom);
    PlayerEnhancedInputComponent->BindAction(ZoomInputAction, ETriggerEvent::Completed, this, &AFPSPlayerController::StopZoom);
  }

  //zoom initialization
  CurrentZoomLevel = 1.0f;
  TargetZoomLevel = 1.0f;
  ZoomInterpSpeed = 5.0f;

  
}

void AFPSPlayerController::Move(const FInputActionValue& Value)
{
  const FVector2D MovementVector = Value.Get<FVector2D>();

  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->Move(Value);
  }
}

void AFPSPlayerController::Look(const FInputActionValue& Value)
{
  const FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->Look(Value);
  }
}

void AFPSPlayerController::StartJump(const FInputActionValue& Value)
{
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->Jump();
  }
}

void AFPSPlayerController::StopJump(const FInputActionValue& Value)
{
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->StopJumping();
  }
}

void AFPSPlayerController::StartAttack(const FInputActionValue& Value)
{
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->StartShooting(Value);
  }
}

void AFPSPlayerController::StopAttack(const FInputActionValue& Value)
{
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->StopShooting(Value);
  }
}


void AFPSPlayerController::StartZoom(const FInputActionValue& Value)
{
  if (AWeapon* Weapon = GetPlayerCharacter()->GetWeapon())
  {
    TargetZoomLevel = Weapon->GetZoomAmount();
  }

  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->GetCameraComponent()->SetFieldOfView(Preferences.FOV / TargetZoomLevel);
  }  
}

void AFPSPlayerController::StopZoom(const FInputActionValue& Value)
{
  //temp without animation
  //TODO make lerp in tick
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->GetCameraComponent()->SetFieldOfView(Preferences.FOV);
  }  
}

void AFPSPlayerController::UpdateZoom()
{
  if (CurrentZoomLevel != TargetZoomLevel)
  {
    CurrentZoomLevel = FMath::FInterpTo(CurrentZoomLevel, TargetZoomLevel, GetWorld()->GetDeltaSeconds(), ZoomInterpSpeed);

    APlayerCharacter* CurrentPlayer = GetPlayerCharacter();
    if (CurrentPlayer)
    {
      CurrentPlayer->GetCameraComponent()->SetFieldOfView(CurrentZoomLevel);
    }
  }
}



void AFPSPlayerController::BeginPlay()
{
  Super::BeginPlay();
  PlayerCameraManager->ViewPitchMin = ViewPitchLimit.X;
  PlayerCameraManager->ViewPitchMax = ViewPitchLimit.Y;
}

APlayerCharacter* AFPSPlayerController::GetPlayerCharacter() const
{
  return Cast<APlayerCharacter>(GetPawn());
}

