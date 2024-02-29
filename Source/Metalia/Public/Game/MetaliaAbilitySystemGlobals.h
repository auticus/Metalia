// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "MetaliaAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
	/* Uses whatever your globals define as your gameplay effect context (refer to your defaultgame.ini)*/
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
