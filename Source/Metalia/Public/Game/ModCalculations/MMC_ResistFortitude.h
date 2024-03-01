// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_ResistFortitude.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMMC_ResistFortitude : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_ResistFortitude();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition StaminaDefinition;
};
