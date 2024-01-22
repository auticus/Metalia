// Copyright Auticus Studios


#include "MetaliaGameplayTags.h"
#include "GameplayTagsManager.h"

FMetaliaGameplayTags FMetaliaGameplayTags::GameplayTags;

void FMetaliaGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("The amount of armor ignored when striking an opponent"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("GameplayTags::InitializeNativeGameplayTags() runs")));
}
