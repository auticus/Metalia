// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMetal.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMMC_MaxMetal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxMetal();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition MetalDefinition;
};
