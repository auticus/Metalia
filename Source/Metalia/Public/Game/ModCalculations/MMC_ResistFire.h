// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_ResistFire.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMMC_ResistFire : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public: 
	UMMC_ResistFire();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};
