// Copyright Auticus Studios


#include "MetaliaAssetManager.h"
#include <MetaliaGameplayTags.h>
#include <AbilitySystemGlobals.h>

UMetaliaAssetManager& UMetaliaAssetManager::Get()
{
    check(GEngine);
    UMetaliaAssetManager* AssetMgr = Cast<UMetaliaAssetManager>(GEngine->AssetManager);
    return *AssetMgr;
}

void UMetaliaAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();
    FMetaliaGameplayTags::InitializeNativeGameplayTags();

    /* the below is REQUIRED if you wish to use Target Data! */
    UAbilitySystemGlobals::Get().InitGlobalData(); // called once as part of project setup to load global data tables & tags
}
