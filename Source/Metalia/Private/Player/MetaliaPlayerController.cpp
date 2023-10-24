// Copyright Auticus Studios


#include "Player/MetaliaPlayerController.h"
#include "EnhancedInputSubsystems.h"

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
