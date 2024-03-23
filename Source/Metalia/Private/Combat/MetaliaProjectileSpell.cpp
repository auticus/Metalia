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

/* Called from the blueprint when anim notify is reached to launch the projectile.  ProjectileTargetLocation if not set goes in forward vector. */
void UMetaliaProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, bool bOverridePitch, float PitchOverride)
{
	AActor* MyCurrentActor = GetAvatarActorFromActorInfo();
	if (MyCurrentActor->HasAuthority() == false) return;

	ICombatInterface* CI = Cast<ICombatInterface>(MyCurrentActor);
	checkf(CI, TEXT("Projectile Spell is owned by something that does not implement the proper combat interface"));

	const FVector SocketLocation = ICombatInterface::Execute_GetProjectileSocketLocation(MyCurrentActor);
	FRotator SocketRotation = ICombatInterface::Execute_GetProjectileSocketForwardRotation(MyCurrentActor);
	if (ProjectileTargetLocation != FVector(0))
	{
		SocketRotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	}
		
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

	Projectile->SetOwningActor(MyCurrentActor);

	// apply the spec handle to the projectile
	CI->SetDamageAbility_Implementation(this);
	Projectile->FinishSpawning(SpellTransform);
}
