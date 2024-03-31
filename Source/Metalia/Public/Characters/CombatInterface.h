// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UNiagaraSystem;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface involving anything requiring combat data.
 */
class METALIA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetProjectileSocketLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FRotator GetProjectileSocketForwardRotation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage(); //TODO: where did you hit me?

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetDeathReactMontage();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	/* Kills the character, dropping their weapon(s) and if RagDollDeath is TRUE will RagDoll Death the character */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die(bool UseRagDollDeath);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AWeapon* GetEquippedWeapon() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<AActor*> GetActorsHitByEquippedWeapon() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CauseDamageToTarget(AActor* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetDamageAbility(UMetaliaDamageAbility* Ability);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetRandomLightAttackMontage() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetLightBloodEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetImpactSocketLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USoundBase* GetEquippedWeaponImpactSound();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USoundBase* GetCharacterDeathSound();
};
