// Copyright Auticus Studios


#include "Player/MetaliaPlayerState.h"
#include "Game/MetaliaAttributeSet.h"
#include "Game/MetaliaAbilitySystemComponent.h"
#include <Net/UnrealNetwork.h>

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

UAttributeSet* AMetaliaPlayerState::GetAttributeSet() const
{
	UMetaliaAttributeSet* AS = Cast<UMetaliaAttributeSet>(AttributeSet);
	return AttributeSet;
}

void AMetaliaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMetaliaPlayerState, Level);
}

void AMetaliaPlayerState::OnRep_Level(int32 OldLevel)
{

}
