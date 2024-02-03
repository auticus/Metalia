// Copyright Auticus Studios


#include "Game/MetaliaAbilitySystemComponent.h"
#include "MetaliaGameplayTags.h"
#include <Game/MetaliaGameplayAbility.h>

/// <summary>
/// Initializes and binds delegates
/// </summary>
void UMetaliaAbilitySystemComponent::Initialize()
{
	// bind delegates
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMetaliaAbilitySystemComponent::ClientEffectApplied);

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

		if (const UMetaliaGameplayAbility* MetaliaAbility = Cast<UMetaliaGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(MetaliaAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
			// GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}

void UMetaliaAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UMetaliaAbilitySystemComponent::AblityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UMetaliaAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, 
													const FGameplayEffectSpec& EffectSpec, 
													FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	OnEffectAssetTagsChanged.Broadcast(TagContainer);
}
