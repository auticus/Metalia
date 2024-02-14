// Copyright Auticus Studios


#include "Combat/MetaliaProjectileSpell.h"
#include <Characters/CombatInterface.h>
#include "Combat/MetaliaProjectile.h"

//todo kill this
#include <Characters/MetaliaCharacter.h>
#include "Player/MetaliaPlayerController.h"

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

	// TODO: Assign Gameplay Spec to projectile to cause an effect
	Projectile->FinishSpawning(SpellTransform);
}
