// Copyright Auticus Studios


#include "Player/MetaliaPlayerController.h"
#include "Characters/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Player/MetaliaPlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/MetaliaHUD.h"
#include "UI/Controllers/MetaliaWidgetController.h"
#include "Game/MetaliaAttributeSet.h"
#include "Game/MetaliaAbilitySystemComponent.h"
#include "Game/Input/MetaliaDataAsset.h"
#include "Game/Input/MetaliaInputComponent.h"
#include "GameplayTagContainer.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "UI/View/DamageTextComponent.h"

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

	UEnhancedInputLocalPlayerSubsystem* localPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (localPlayerSubsystem)
	{
		localPlayerSubsystem->AddMappingContext(MetaliaPlayerContext, 0);
	}
	
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
	
	UMetaliaInputComponent* MetaliaInputComponent = CastChecked<UMetaliaInputComponent>(InputComponent);

	// Bind your actions
	MetaliaInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMetaliaPlayerController::Move);
	MetaliaInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AMetaliaPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{

}

void AMetaliaPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetMetaliaAbilitySystemComponent() == nullptr) return;
	GetMetaliaAbilitySystemComponent()->AblityInputTagReleased(InputTag);
}

void AMetaliaPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetMetaliaAbilitySystemComponent() == nullptr) return;
	GetMetaliaAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
}

UMetaliaAbilitySystemComponent* AMetaliaPlayerController::GetMetaliaAbilitySystemComponent()
{
	// lazy load the ability system component.  If its not set yet just return null
	if (MetaliaAbilitySystemComponent == nullptr)
	{
		MetaliaAbilitySystemComponent = Cast<UMetaliaAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return MetaliaAbilitySystemComponent;
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
	//CurrentEnemy = Cast<IEnemyInterface>(CursorHit.GetActor()); // if not valid interface actor, will be null
	CurrentEnemy.SetObject(Cast<UObject>(CursorHit.GetActor()));

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

void AMetaliaPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bIsBlocked, bool bIsCriticalHit)
{
	// This is RPC call
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		// create the bubble up damage component, attach it to character, then immediately detach so it floats on its own off the character
		UDamageTextComponent* DamageText = NewObject <UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bIsBlocked, bIsCriticalHit);
	}
}