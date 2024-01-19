// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FMetaliaGameplayTags
{
public:
	static const FMetaliaGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

private:
	static FMetaliaGameplayTags GameplayTags;
};
