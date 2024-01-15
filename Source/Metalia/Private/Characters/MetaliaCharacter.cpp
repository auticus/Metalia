// Copyright Auticus Studios


#include "Characters/MetaliaCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MetaliaPlayerState.h"
#include "AbilitySystemComponent.h"
#include <Game/MetaliaAbilitySystemComponent.h>
#include <Game/MetaliaAttributeSet.h>

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
	UE_LOG(LogTemp, Warning, TEXT("Character initialized, health = %f"), health);
}

int32 AMetaliaCharacter::GetCharacterLevel() const
{
	const AMetaliaPlayerState* MetaliaPlayerState = GetPlayerState<AMetaliaPlayerState>();
	check(MetaliaPlayerState);
	return MetaliaPlayerState->GetCharacterLevel();
}
