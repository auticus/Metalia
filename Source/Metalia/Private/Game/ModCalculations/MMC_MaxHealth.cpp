// Copyright Auticus Studios


#include "Game/ModCalculations/MMC_MaxHealth.h"
#include "Game/MetaliaAttributeSet.h"
#include <Characters/CombatInterface.h>

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDefinition.AttributeToCapture = UMetaliaAttributeSet::GetVigorAttribute();
	VigorDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDefinition.bSnapshot = false;  

	RelevantAttributesToCapture.Add(VigorDefinition);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather the tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDefinition, Spec, EvaluationParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	// note that STEPHEN uses GetSourceObject() here which returns null, but GetEffectCauser seems to work fine.  Here that is ok because
	// the effect causer should be the character itself anyway (the target i guess?)  There is also a GetInstigator	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetEffectCauser());
	
	if (CombatInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("MMC_MaxHealth has no Combat Interface object and defaults to level = 1, Vigor = %f"), Vigor);
		return 20.f + (Vigor);
	}

	const int32 Level = CombatInterface->GetCharacterLevel_Implementation();
	return BaseHealth + (VigorCoefficient * Vigor) + (LevelCoefficient * Level);
}
