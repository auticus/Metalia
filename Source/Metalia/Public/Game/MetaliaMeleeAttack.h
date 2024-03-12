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

	/* The class that represents the projectile being cast */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<AWeapon> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInitialized;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	/* Assigns the spec handle to the weapon so that it can do damage when it strikes an enemy */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void InitializeDamageSpecHandleWithWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeapon(AWeapon* NewWeapon);
};
