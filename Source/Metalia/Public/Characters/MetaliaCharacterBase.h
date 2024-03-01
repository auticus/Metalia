// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Characters/CombatInterface.h"
#include "GameplayTagContainer.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	/* The name of all sockets that should exist on all weapon tips for projectile purposes */
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	/* END DISSOLVE */

	/* a bool value determining if the character is alive */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsAlive;

	/* Whether or not the character is in a blocking state */
	UPROPERTY(EditAnywhere, Category = "Combat")
	bool bHitBlocking = false;

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

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	virtual UAnimMontage* GetDeathReactMontage_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual bool GetIsAlive() const;

	UFUNCTION(BlueprintCallable)
	virtual bool GetIsBlocking() const;
	
	virtual void Die_Implementation(bool UseRagDollDeath) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(bool UseRagDollDeath);

protected:
	virtual void InitAbilityActorInfo();

	/* Will apply the Default Game Effects set on the character or blueprint to itself to set the starting scores.  Override to default to something else.*/
	virtual void InitializeDefaultAttributes();
	virtual void InitializeDelegateBroadcastersAndBroadcastDefaults();
	virtual void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float EffectLevel);
	void AddCharacterAbilities();
	virtual FVector GetProjectileSocketLocation_Implementation() override;
	virtual FRotator GetProjectileSocketForwardRotation_Implementation() override;

	/* Disolve the character and any weapons it is holding */
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
};
