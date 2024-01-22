// Copyright Auticus Studios


#include "MetaliaAssetManager.h"
#include <MetaliaGameplayTags.h>

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
}
