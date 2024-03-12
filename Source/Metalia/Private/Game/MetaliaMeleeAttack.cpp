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

	AActor* MyCurrentActor = GetAvatarActorFromActorInfo();
	ICombatInterface* Combat = Cast<ICombatInterface>(MyCurrentActor);

	if (!MyCurrentActor->HasAuthority()) return;
	
	// Assign the gameplay effect to the projectile so that it has a purpose in life
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

	// assign the damage tag and damage that this projectile spell will do
	FMetaliaGameplayTags Tags = FMetaliaGameplayTags::Get();

	for (auto& Pair : DamageTypes)
	{
		// loop through each damage type, pull its type (key ie. Damage_Fire) and then send its raw scaled damage back
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}

	// apply the spec handle to the projectile
	Weapon->DamageEffectSpecHandle = SpecHandle;
	bIsInitialized = true;
}

void UMetaliaMeleeAttack::SetWeapon(AWeapon* NewWeapon)
{
	Weapon = NewWeapon;
}
