// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include <AbilitySystemComponent.h>

/**
 * 
 */
class METALIA_API FMetaliaGameplayTags
{
public:
	static const FMetaliaGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Stamina;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Metal;
	FGameplayTag Attributes_Primary_Will;

	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_Block;
	FGameplayTag Attributes_Secondary_CarryCapacity;
	FGameplayTag Attributes_Secondary_Critical;
	FGameplayTag Attributes_Secondary_CriticalDamage;
	FGameplayTag Attributes_Secondary_DamageModifier;
	FGameplayTag Attributes_Secondary_Defense;
	FGameplayTag Attributes_Secondary_Fortitude;
	FGameplayTag Attributes_Secondary_HealthRegen;
	FGameplayTag Attributes_Secondary_ManaRegen;
	FGameplayTag Attributes_Secondary_Resolve;
	FGameplayTag Attributes_Secondary_Speed;

	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_MaxHealth;
	FGameplayTag Attributes_Vital_Mana;
	FGameplayTag Attributes_Vital_MaxMana;
	FGameplayTag Attributes_Vital_Fatigue;
	FGameplayTag Attributes_Vital_MaxFatigue;

private:
	static FMetaliaGameplayTags GameplayTags;
};