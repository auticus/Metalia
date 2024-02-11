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

FVector UMetaliaProjectileSpell::GetSocketLocationFromExecutingActor() const
{
	// interesting way of invoking an interface.  Statically passing in the object.
	// now for lolz we have to figure out why the actor coming in is not my character who should be implementing ICombatInterface
	AActor* MyCurrentActor = GetAvatarActorFromActorInfo();
	ICombatInterface* Combat = Cast<ICombatInterface>(MyCurrentActor);

	if (!Combat)
	{
		// if it passed back the Controller, you need to dig the character out of that
		// if it did not pass back a controller and something else is haywire, thats bad.

		// this could be a problem with AI controlled items but we shall see
		UE_LOG(LogTemp, Warning, TEXT("Getting the socket from executing actor required doing the magical controller cast thing"));
		AMetaliaPlayerController* Controller = Cast<AMetaliaPlayerController>(MyCurrentActor);
		check(Controller);

		MyCurrentActor = Cast<AMetaliaCharacterBase>(Controller->GetCharacter());
		check(MyCurrentActor);
	}
		
	return ICombatInterface::Execute_GetProjectileSocketLocation(MyCurrentActor);
}

/* Called from the blueprint when anim notify is reached to launch the projectile */
void UMetaliaProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = GetSocketLocationFromExecutingActor();

	FTransform SpellTransform;
	SpellTransform.SetLocation(SocketLocation);

	//TODO: orient rotation towards target

	AMetaliaProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMetaliaProjectile>(
		ProjectileClass,
		SpellTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()), // the instigator
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// TODO: Assign Gameplay Spec to projectile to cause an effect
	Projectile->FinishSpawning(SpellTransform);
}
