// Copyright Auticus Studios


#include "Game/MetaliaMeleeAttack.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystemComponent.h"
#include <MetaliaGameplayTags.h>

void UMetaliaMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMetaliaMeleeAttack::InitializeDamageSpecHandleWithWeapon()
{
	if (Weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Melee Attack DamageAbility was initialized but the weapon was not set."));
		return;
	}

	// apply the spec handle to the projectile
	Weapon->AssignedDamageAbility = this;
	bIsInitialized = true;
}

void UMetaliaMeleeAttack::SetWeapon(AWeapon* NewWeapon)
{
	Weapon = NewWeapon;
}
