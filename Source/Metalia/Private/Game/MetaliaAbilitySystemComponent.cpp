// Copyright Auticus Studios


#include "Game/MetaliaAbilitySystemComponent.h"

/// <summary>
/// Initializes and binds delegates
/// </summary>
void UMetaliaAbilitySystemComponent::Initialize()
{
	// bind delegates
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMetaliaAbilitySystemComponent::EffectApplied);
}

void UMetaliaAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, 
													const FGameplayEffectSpec& EffectSpec, 
													FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	OnEffectAssetTagsChanged.Broadcast(TagContainer);
}
