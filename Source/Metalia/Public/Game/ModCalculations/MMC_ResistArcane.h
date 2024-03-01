// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_ResistArcane.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMMC_ResistArcane : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_ResistArcane();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition WillDefinition;
};
