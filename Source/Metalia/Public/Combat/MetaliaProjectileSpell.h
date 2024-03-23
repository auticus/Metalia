// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Game/MetaliaDamageAbility.h"
#include "MetaliaProjectileSpell.generated.h"

class AMetaliaProjectile;

/**
 * Gameplay Ability that represents a projectile spell.
 */
UCLASS()
class METALIA_API UMetaliaProjectileSpell : public UMetaliaDamageAbility
{
	GENERATED_BODY()

protected:

	/* The class that represents the projectile being cast */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMetaliaProjectile> ProjectileClass;

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	/* Called from the blueprint when anim notify is reached to launch the projectile.  ProjectileTargetLocation if not set goes in forward vector. */
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, bool bOverridePitch, float PitchOverride);
};
