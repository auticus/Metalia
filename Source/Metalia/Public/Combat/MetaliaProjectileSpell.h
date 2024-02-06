// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Game/MetaliaGameplayAbility.h"
#include "MetaliaProjectileSpell.generated.h"

/**
 * Gameplay Ability that represents a projectile spell.
 */
UCLASS()
class METALIA_API UMetaliaProjectileSpell : public UMetaliaGameplayAbility
{
	GENERATED_BODY()

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
};
