// Copyright Auticus Studios


#include "Player/MetaliaPlayerState.h"
#include "Game/MetaliaAttributeSet.h"
#include "Game/MetaliaAbilitySystemComponent.h"

AMetaliaPlayerState::AMetaliaPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UMetaliaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMetaliaAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AMetaliaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}