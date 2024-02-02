// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MetaliaGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	/// <summary>
	/// The startup input tag at the beginning of the game.  This is only useful on startup.
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;
	
};
