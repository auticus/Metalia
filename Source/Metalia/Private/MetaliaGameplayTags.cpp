// Copyright Auticus Studios


#include "MetaliaGameplayTags.h"
#include "GameplayTagsManager.h"

FMetaliaGameplayTags FMetaliaGameplayTags::GameplayTags;

void FMetaliaGameplayTags::InitializeNativeGameplayTags()
{
	// primary attributes
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("How strong the character is"));
	GameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Agility"), FString("How agile and quick the character is"));
	GameplayTags.Attributes_Primary_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Stamina"), FString("How much endurance the character has"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("How healthy the character is"));
	GameplayTags.Attributes_Primary_Metal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Metal"), FString("How strong in the powers of metal the character is"));
	GameplayTags.Attributes_Primary_Will = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Will"), FString("How strong in will the character is"));

	// vital attributes
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("The amount of health a character has"));
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"), FString("The max amount of health a character has"));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("The amount of metal mana a character has"));
	GameplayTags.Attributes_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxMana"), FString("The max amount of metal mana a character has"));
	GameplayTags.Attributes_Vital_Fatigue = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Fatigue"), FString("The amount of stamina a character has"));
	GameplayTags.Attributes_Vital_MaxFatigue = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxFatigue"), FString("The max amount of stamina a character has"));

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
	// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("GameplayTags::InitializeNativeGameplayTags() runs")));
}
