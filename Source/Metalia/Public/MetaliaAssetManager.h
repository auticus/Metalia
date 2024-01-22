// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MetaliaAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UMetaliaAssetManager& Get();

protected:
	/* Called from the Unreal Engine to load assets */
	virtual void StartInitialLoading() override;
	
};
