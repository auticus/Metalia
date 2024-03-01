// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_ResistLightning.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMMC_ResistLightning : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_ResistLightning();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

};
