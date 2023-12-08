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
	GENERATED_BODY()
	
public:
	/// <summary>
	/// Delegate that holds the tag container that will be broadcast when the tags change
	/// </summary>
	FEffectAssetTags OnEffectAssetTagsChanged;

public:
	void Initialize();

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
