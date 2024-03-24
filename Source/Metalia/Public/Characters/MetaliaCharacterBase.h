// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Items/Inventory.h"
#include "Characters/CombatInterface.h"
#include "MetaliaCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

UCLASS(Abstract)
class METALIA_API AMetaliaCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AMetaliaCharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float BaseWalkSpeed;

	/* a decimal value that represents what percentage of the time the character will ragdoll on death vs an animation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float PercentToUseRagDollDeath;

	/* The damage effect spec handle that will be used to cause the effect of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	TObjectPtr<class UMetaliaDamageAbility> AssignedDamageAbility;

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultResistanceAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributeInitialization;

	/* Dissolve Effects */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	/* END DISSOLVE */

	/* a bool value determining if the character is alive */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsDead;

	/* Whether or not the character is in a blocking state */
	UPROPERTY(EditAnywhere, Category = "Combat")
	bool bHitBlocking = false;

	/* Class holding the inventory object that the character starts with */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UInventory> InventoryClass;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UInventory> Inventory;

	/* Animation Montages */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<UAnimMontage*> LightAttackMontages;
	/* END Animation Montages */

	/* For thrown, breath, etc attacks that do not stem from a weapon that is carried */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProjectileSocketName;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> DeathReactMontage;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet;  }

	virtual int32 GetCharacterLevel_Implementation() const override;

	/* Combat Interface implementation to get the hit react montage */
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	/* Combat Interface implementation to get the death react montage */
	virtual UAnimMontage* GetDeathReactMontage_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual bool GetIsBlocking() const;
	
	virtual void Die_Implementation(bool UseRagDollDeath) override;

	virtual float GetHealth_Implementation() const override;

	virtual float GetMaxHealth_Implementation() const override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(bool UseRagDollDeath);

	virtual bool IsDead_Implementation() const override;

	virtual AActor* GetAvatar_Implementation() override;

	virtual AWeapon* GetEquippedWeapon_Implementation() const override;

	virtual void SetDamageAbility_Implementation(UMetaliaDamageAbility* Ability) override;

	virtual void CauseDamageToTarget_Implementation(AActor* Target) override;

	UAnimMontage* GetRandomLightAttackMontage_Implementation() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitAbilityActorInfo();

	/* Will apply the Default Game Effects set on the character or blueprint to itself to set the starting scores.  Override to default to something else.*/
	virtual void InitializeDefaultAttributes();
	virtual void InitializeDelegateBroadcastersAndBroadcastDefaults();
	virtual void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float EffectLevel);
	void AddCharacterAbilities();
	virtual FVector GetProjectileSocketLocation_Implementation() override;
	virtual FRotator GetProjectileSocketForwardRotation_Implementation() override;

	/* Disolve the character and any weapons it is holding */
	UFUNCTION(Client, Reliable)
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
};
