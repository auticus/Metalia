// Copyright Auticus Studios


#include "Game/MetaliaAbilitySystemComponent.h"
#include "MetaliaGameplayTags.h"

/// <summary>
/// Initializes and binds delegates
/// </summary>
void UMetaliaAbilitySystemComponent::Initialize()
{
	// bind delegates
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMetaliaAbilitySystemComponent::EffectApplied);

	/* DEBUG CODE */
	/*
	const FMetaliaGameplayTags& GameplayTags = FMetaliaGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Primary_Strength.ToString()));
	*/
}

void UMetaliaAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		int32 Level = 1;
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, Level);

		// can either give ability or give and activate them
		GiveAbility(AbilitySpec);
		// GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UMetaliaAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, 
													const FGameplayEffectSpec& EffectSpec, 
													FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	OnEffectAssetTagsChanged.Broadcast(TagContainer);
}
