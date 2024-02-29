// Copyright Auticus Studios


#include "Game/MetaliaAbilitySystemGlobals.h"
#include "Game/FAuraGameplayEffectContext.h"

FGameplayEffectContext* UMetaliaAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
