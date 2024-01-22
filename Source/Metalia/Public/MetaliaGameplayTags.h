// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include <AbilitySystemComponent.h>

/**
 * 
 */
class METALIA_API FMetaliaGameplayTags
{
public:
	static const FMetaliaGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Secondary_ArmorPenetration;

private:
	static FMetaliaGameplayTags GameplayTags;
};
