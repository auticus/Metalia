// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Game/MetaliaDamageAbility.h"
#include "Items/Weapon.h"
#include "MetaliaMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaMeleeAttack : public UMetaliaDamageAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
};
