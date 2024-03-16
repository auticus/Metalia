// Copyright Auticus Studios


#include "Game/MetaliaMeleeAttack.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystemComponent.h"
#include <MetaliaGameplayTags.h>

void UMetaliaMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* MyCurrentActor = GetAvatarActorFromActorInfo();
	ICombatInterface* CI = Cast<ICombatInterface>(MyCurrentActor);
	checkf(CI, TEXT("Melee Attack Ability is owned by something that does not implement the proper combat interface"));

	// apply the spec handle to the projectile
	CI->SetDamageAbility_Implementation(this);
}
