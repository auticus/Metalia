// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MetaliaAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaAbilitySystemComponent : public UAbilitySystemComponent
{
	// It is stated the best place to put this component is on Player State so that everyone has access to read everyone's abilities

	GENERATED_BODY()
	
public:
	/// <summary>
	/// Delegate that holds the tag container that will be broadcast when the tags change
	/// </summary>
	FEffectAssetTags OnEffectAssetTagsChanged;

public:
	void Initialize();

	UFUNCTION()
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AblityInputTagReleased(const FGameplayTag& InputTag);

protected:

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
