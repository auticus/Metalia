// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	/* The amount of base health to start with */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Values")
	float BaseHealth;

	/* The amount of health to add equal to Vigor multiplied by this amount */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Values")
	float VigorCoefficient;

	/* The amount of health to add equal to level multiplied by this amount  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Values")
	float LevelCoefficient;

public:
	UMMC_MaxHealth();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition VigorDefinition;
	
};
