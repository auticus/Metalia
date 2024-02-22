// Copyright Auticus Studios


#include "Combat/MetaliaProjectileSpell.h"
#include <Characters/CombatInterface.h>
#include "Combat/MetaliaProjectile.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystemComponent.h"

//todo kill this
#include <Characters/MetaliaCharacter.h>
#include "Player/MetaliaPlayerController.h"
#include <MetaliaGameplayTags.h>

void UMetaliaProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);	
}

/* Called from the blueprint when anim notify is reached to launch the projectile */
void UMetaliaProjectileSpell::SpawnProjectile(bool bOverridePitch, float PitchOverride)
{
	AActor* MyCurrentActor = GetAvatarActorFromActorInfo();
	ICombatInterface* Combat = Cast<ICombatInterface>(MyCurrentActor);

	const bool bIsServer = MyCurrentActor->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetProjectileSocketLocation(MyCurrentActor);
	FRotator SocketRotation = ICombatInterface::Execute_GetProjectileSocketForwardRotation(MyCurrentActor);
	if (bOverridePitch)
	{
		SocketRotation.Pitch = PitchOverride;
	}

	FTransform SpellTransform;
	SpellTransform.SetLocation(SocketLocation);
	SpellTransform.SetRotation(SocketRotation.Quaternion());

	AMetaliaProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMetaliaProjectile>(
		ProjectileClass,
		SpellTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()), // the instigator
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// Assign the gameplay effect to the projectile so that it has a purpose in life
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

	// assign the damage tag and damage that this projectile spell will do
	FMetaliaGameplayTags Tags = FMetaliaGameplayTags::Get();
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Tags.Damage, 25.f);
	
	// apply the spec handle to the projectile
	Projectile->DamageEffectSpecHandle = SpecHandle;
	Projectile->FinishSpawning(SpellTransform);
}
