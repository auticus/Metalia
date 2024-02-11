// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Game/MetaliaGameplayAbility.h"
#include "MetaliaProjectileSpell.generated.h"

class AMetaliaProjectile;

/**
 * Gameplay Ability that represents a projectile spell.
 */
UCLASS()
class METALIA_API UMetaliaProjectileSpell : public UMetaliaGameplayAbility
{
	GENERATED_BODY()

protected:

	/* The class that represents the projectile being cast */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMetaliaProjectile> ProjectileClass;

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	FVector GetSocketLocationFromExecutingActor() const;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile();
};
