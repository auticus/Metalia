// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MetaliaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void Initialize();

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
