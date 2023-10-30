// Copyright Auticus Studios


#include "Player/MetaliaPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

AMetaliaPlayerState::AMetaliaPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AMetaliaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}