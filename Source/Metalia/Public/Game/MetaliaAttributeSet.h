// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "MetaliaAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER (PropertyName)

template<class T>
using TStaticAttributeFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties()
	{

	}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceComponent = nullptr;

	UPROPERTY()
	AActor* SourceActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetComponent = nullptr;

	UPROPERTY()
	AActor* TargetActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * Attribute set for Metalia characters.
 */
UCLASS()
class METALIA_API UMetaliaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	TMap<FGameplayTag, TStaticAttributeFuncPtr<FGameplayAttribute()>> TagsToAttributesMap;
	FGuid AttributeSetId;

	//* PRIMARY ATTRIBUTES *//
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Agility, Category = "Primary Attributes")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Agility);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Primary Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Vigor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Willpower, Category = "Primary Attributes")
	FGameplayAttributeData Willpower;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Willpower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Metal, Category = "Primary Attributes")
	FGameplayAttributeData Metal;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Metal);

	//* SECONDARY ATTRIBUTES *//
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Block, Category = "Secondary Attributes")
	FGameplayAttributeData Block;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Block);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CarryCapacity, Category = "Secondary Attributes")
	FGameplayAttributeData CarryCapacity;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, CarryCapacity);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Critical, Category = "Secondary Attributes")
	FGameplayAttributeData Critical;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Critical);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, CriticalDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageModifier, Category = "Secondary Attributes")
	FGameplayAttributeData DamageModifier;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, DamageModifier);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Secondary Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Defense);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Fortitude, Category = "Secondary Attributes")
	FGameplayAttributeData Fortitude;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Fortitude);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, HealthRegen);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MetalManaRegen, Category = "Secondary Attributes")
	FGameplayAttributeData MetalManaRegen;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, MetalManaRegen);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resolve, Category = "Secondary Attributes")
	FGameplayAttributeData Resolve;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Resolve);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Speed, Category = "Secondary Attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Speed);

	//* VITAL ATTRIBUTES *//

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MetalMana, Category = "Vital Attributes")
	FGameplayAttributeData MetalMana;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, MetalMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMetalMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMetalMana;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, MaxMetalMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Fatigue, Category = "Vital Attributes")
	FGameplayAttributeData Fatigue;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Fatigue);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxFatigue, Category = "Vital Attributes")
	FGameplayAttributeData MaxFatigue;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, MaxFatigue);

	//* META ATTRIBUTES *//
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, IncomingDamage);

private:
	const float DefaultVitalityScore = 20.f; // TODO: this will be shuttled out for the appropriate attributes when STEPHEN gets to it

public:
	UMetaliaAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_MetalMana(const FGameplayAttributeData& OldMetalMana) const;

	UFUNCTION()
	void OnRep_MaxMetalMana(const FGameplayAttributeData& OldMaxMetalMana) const;

	UFUNCTION()
	void OnRep_MaxFatigue(const FGameplayAttributeData& OldMaxFatigue) const;

	UFUNCTION()
	void OnRep_Fatigue(const FGameplayAttributeData& OldFatigue) const;


	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Agility(const FGameplayAttributeData& OldAgility) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_Willpower(const FGameplayAttributeData& OldWillpower) const;

	UFUNCTION()
	void OnRep_Metal(const FGameplayAttributeData& OldMetal) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_Block(const FGameplayAttributeData& OldBlock) const;

	UFUNCTION()
	void OnRep_CarryCapacity(const FGameplayAttributeData& OldCarryCapacity) const;

	UFUNCTION()
	void OnRep_Critical(const FGameplayAttributeData& OldCritical) const;

	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage) const;

	UFUNCTION()
	void OnRep_DamageModifier(const FGameplayAttributeData& OldDamageModifier) const;

	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldDefense) const;

	UFUNCTION()
	void OnRep_Fortitude(const FGameplayAttributeData& OldFortitude) const;

	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const;

	UFUNCTION()
	void OnRep_MetalManaRegen(const FGameplayAttributeData& OldMetalManaRegen) const;

	UFUNCTION()
	void OnRep_Resolve(const FGameplayAttributeData& OldResolve) const;

	UFUNCTION()
	void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	void AddPrimaryAttributesToMap();
	void AddSecondaryAttributesToMap();
	void HandleDamageAttribute();
};
