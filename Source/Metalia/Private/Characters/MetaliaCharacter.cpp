// Copyright Auticus Studios


#include "Characters/MetaliaCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MetaliaPlayerState.h"
#include "AbilitySystemComponent.h"
#include <Game/MetaliaAbilitySystemComponent.h>
#include <Game/MetaliaAttributeSet.h>
#include <Player/MetaliaPlayerController.h>
#include <UI/MetaliaHUD.h>
#include "UI/Controllers/MetaliaWidgetController.h"

AMetaliaCharacter::AMetaliaCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true; // top-down game, common setting
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AMetaliaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info on the server.
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AMetaliaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

void AMetaliaCharacter::InitAbilityActorInfo()
{
	AMetaliaPlayerState* MetaliaPlayerState = GetPlayerState<AMetaliaPlayerState>();
	check(MetaliaPlayerState);
	MetaliaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MetaliaPlayerState, this);

	AbilitySystemComponent = MetaliaPlayerState->GetAbilitySystemComponent();
	AttributeSet = MetaliaPlayerState->GetAttributeSet();

	Cast<UMetaliaAbilitySystemComponent>(MetaliaPlayerState->GetAbilitySystemComponent())->Initialize();
	InitializeDefaultAttributes();

	UMetaliaAttributeSet* metalia = Cast<UMetaliaAttributeSet>(AttributeSet);
	float health = metalia->GetHealth();

	// at this point we have to initialize the HUD.  This requires a player controller but if we are here at the character stage
	// then we already have had a controller created.  note that not everyone has a controller... only if this is the player playing.
	// replicated players will not have this and thats fine we dont want to set a HUD for them.
	if (AMetaliaPlayerController* PC = Cast<AMetaliaPlayerController>(GetController()))
	{
		if (AMetaliaHUD* HUD = Cast<AMetaliaHUD>(PC->GetHUD()))
		{
			FWidgetControllerParams params = { PC, MetaliaPlayerState, AbilitySystemComponent, AttributeSet };
			HUD->InitializeOverlay(params);
		}
	}
}

int32 AMetaliaCharacter::GetCharacterLevel_Implementation() const
{
	const AMetaliaPlayerState* MetaliaPlayerState = GetPlayerState<AMetaliaPlayerState>();
	check(MetaliaPlayerState);
	return MetaliaPlayerState->GetCharacterLevel_Implementation();
}
