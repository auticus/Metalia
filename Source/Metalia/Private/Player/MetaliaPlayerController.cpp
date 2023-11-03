// Copyright Auticus Studios


#include "Player/MetaliaPlayerController.h"
#include "Characters/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Player/MetaliaPlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/MetaliaHUD.h"
#include "UI/Controllers/MetaliaWidgetController.h"

AMetaliaPlayerController::AMetaliaPlayerController() :
	GamepadDeadZone(0.25f)
{
	bReplicates = true;
}

void AMetaliaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AMetaliaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(MetaliaPlayerContext);
	CreateHud();

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

void AMetaliaPlayerController::CreateHud()
{
	if (GetWorld() == nullptr || GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		// this is a server instance of the controller and we don't need to create a HUD
		return;
	}

	AMetaliaPlayerState* MetaliaPlayerState = GetPlayerState<AMetaliaPlayerState>();
	check(MetaliaPlayerState);

	MetaliaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MetaliaPlayerState, this);
	UAbilitySystemComponent* AbilitySystemComponent = MetaliaPlayerState->GetAbilitySystemComponent();
	UAttributeSet* AttributeSet = MetaliaPlayerState->GetAttributeSet();

	AMetaliaHUD* HUD = Cast<AMetaliaHUD>(GetHUD());

	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController::CreateHud trying to draw HUD fails - HUD NOT SET!"));
		return;
	}

	FWidgetControllerParams params(this, PlayerState, AbilitySystemComponent, AttributeSet);
	HUD->InitializeOverlay(params);
}

void AMetaliaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	double InputX = InputAxisVector.X;
	double InputY = InputAxisVector.Y;

	// check for deadzone and if less than that value, cull the value completely 
	// to get rid of joystick drift.
	if (InputAxisVector.Length() < GamepadDeadZone)
	{
		InputX = 0;
		InputY = 0;
	}

	if (APawn* pawn = GetPawn<APawn>())
	{
		pawn->AddMovementInput(ForwardDirection, InputY);
		pawn->AddMovementInput(RightDirection, InputX);
	}
}

void AMetaliaPlayerController::CursorTrace()
{
	FHitResult CursorHit;

	// note this requires meshes to block the Visible channel to work
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastEnemy = CurrentEnemy;
	CurrentEnemy = Cast<IEnemyInterface>(CursorHit.GetActor()); // if not valid interface actor, will be null

	if (LastEnemy == nullptr && CurrentEnemy == nullptr) return;
	else if (LastEnemy == nullptr && CurrentEnemy != nullptr)
	{
		CurrentEnemy->HighlightActor();
	}
	else if (LastEnemy != nullptr && CurrentEnemy == nullptr)
	{
		LastEnemy->UnhighlightActor();
	}
	else if (LastEnemy != nullptr && CurrentEnemy != nullptr && LastEnemy != CurrentEnemy)
	{
		LastEnemy->UnhighlightActor();
		CurrentEnemy->HighlightActor();
	}
}
