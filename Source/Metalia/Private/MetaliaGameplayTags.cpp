// Copyright Auticus Studios


#include "MetaliaGameplayTags.h"
#include "GameplayTagsManager.h"

FMetaliaGameplayTags FMetaliaGameplayTags::GameplayTags;

void FMetaliaGameplayTags::InitializeNativeGameplayTags()
{
	InitializePrimaryAttributes();
	InitializeVitalAttributes();
	InitializeSecondaryAttributes();
	InitializeInputTags();
	InitializeEffectTags();
	InitializeMiscTags();
}

void FMetaliaGameplayTags::InitializePrimaryAttributes()
{
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("How strong the character is"));
	GameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Agility"), FString("How agile and quick the character is"));
	GameplayTags.Attributes_Primary_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Stamina"), FString("How much endurance the character has"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("How healthy the character is"));
	GameplayTags.Attributes_Primary_Metal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Metal"), FString("How strong in the powers of metal the character is"));
	GameplayTags.Attributes_Primary_Will = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Will"), FString("How strong in will the character is"));
}

void FMetaliaGameplayTags::InitializeVitalAttributes()
{
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("The amount of health a character has"));
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"), FString("The max amount of health a character has"));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("The amount of metal mana a character has"));
	GameplayTags.Attributes_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxMana"), FString("The max amount of metal mana a character has"));
	GameplayTags.Attributes_Vital_Fatigue = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Fatigue"), FString("The amount of stamina a character has"));
	GameplayTags.Attributes_Vital_MaxFatigue = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxFatigue"), FString("The max amount of stamina a character has"));
}

void FMetaliaGameplayTags::InitializeSecondaryAttributes()
{
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("The amount of armor ignored when striking an opponent"));
	GameplayTags.Attributes_Secondary_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Block"), FString("% of physical damage you can ignore extra, based on items or abilities"));
	GameplayTags.Attributes_Secondary_CarryCapacity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CarryCapacity"), FString("The amount of equipment you can carry"));
	GameplayTags.Attributes_Secondary_Critical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Critical"), FString("Percentage chance a hit will do critical damage"));
	GameplayTags.Attributes_Secondary_CriticalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalDamage"), FString("Bonus damage a critical hit does"));
	GameplayTags.Attributes_Secondary_DamageModifier = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.DamageModifier"), FString("Damage modifier to physical attacks added to the weapon"));
	GameplayTags.Attributes_Secondary_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Defense"), FString("The amount of damage reduced when struck based on armor and agility"));
	GameplayTags.Attributes_Secondary_Fortitude = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Fortitude"), FString("Defense against poisons, diseases, etc based on Stamina"));
	GameplayTags.Attributes_Secondary_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegen"), FString("The amount of health regenerated per second"));
	GameplayTags.Attributes_Secondary_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegen"), FString("The amount of metal mana regenderated per second"));
	GameplayTags.Attributes_Secondary_Resolve = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Resolve"), FString("Defense against mental attacks based on Wil"));
	GameplayTags.Attributes_Secondary_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Speed"), FString("The speed at which the character moves based on Agi"));
}

void FMetaliaGameplayTags::InitializeInputTags()
{
	GameplayTags.InputTag_Primary = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Primary"), FString("Primary action input"));
	GameplayTags.InputTag_Secondary = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Secondary"), FString("Secondary action input"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Ability 1 input"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Ability 2 input"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Ability 3 input"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Ability 4 input"));
}

void FMetaliaGameplayTags::InitializeEffectTags()
{
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("When hit, the tag that denotes to react"));
	GameplayTags.Effects_DeathReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.DeathReact"), FString("When dying, the tag that denotes to react and die"));
}

void FMetaliaGameplayTags::InitializeMiscTags()
{
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
}
