// Copyright Auticus Studios


#include "Player/MetaliaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AMetaliaPlayerController::AMetaliaPlayerController()
{
	bReplicates = true;
}

void AMetaliaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(MetaliaPlayerContext);

	UEnhancedInputLocalPlayerSubsystem* localPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(localPlayerSubsystem);
	localPlayerSubsystem->AddMappingContext(MetaliaPlayerContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);
}

void AMetaliaPlayerController::SetupInputComponent()
{
	// if you see the red squiggly here... ignore it.
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind your actions
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMetaliaPlayerController::Move);
}

void AMetaliaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* pawn = GetPawn<APawn>())
	{
		pawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		pawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
