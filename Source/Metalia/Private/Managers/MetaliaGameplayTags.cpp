// Copyright Auticus Studios


#include "Managers/MetaliaGameplayTags.h"
#include "GameplayTagsManager.h"

void FMetaliaGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Percentage of armor ignored when hitting an opponent."));
}
