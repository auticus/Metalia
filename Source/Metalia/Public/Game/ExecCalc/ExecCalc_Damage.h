// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

class AMetaliaCharacterBase;

/**
 * 
 */
UCLASS()
class METALIA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:
	float ProcessDamageAfterBlock(
		AMetaliaCharacterBase* TargetCharacterBase,
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FAggregatorEvaluateParameters EvaluationParameters,
		float Damage) const;
	
	float ProcessDamageAfterDefense(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FAggregatorEvaluateParameters EvaluationParameters,
		float Damage) const;
	
	float ProcessPotentialCriticalHit(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FAggregatorEvaluateParameters EvaluationParameters,
		float Damage) const;
};
