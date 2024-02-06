// Copyright Auticus Studios


#include "Game/ModCalculations/MMC_MaxMetal.h"
#include "Game/MetaliaAttributeSet.h"
#include <Characters/CombatInterface.h>

UMMC_MaxMetal::UMMC_MaxMetal()
{
	MetalDefinition.AttributeToCapture = UMetaliaAttributeSet::GetMetalAttribute();
	MetalDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MetalDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(MetalDefinition);
}

float UMMC_MaxMetal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather the tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Metal = 0.f;
	GetCapturedAttributeMagnitude(MetalDefinition, Spec, EvaluationParameters, Metal);
	Metal = FMath::Max<float>(Metal, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	if (CombatInterface == nullptr)
	{
		return 80.f + (2.5f * Metal) + (10.f);
	}
	const int32 Level = CombatInterface->GetCharacterLevel_Implementation();

	return 50.f + (2.5f * Metal) + (10.f * Level);
}
