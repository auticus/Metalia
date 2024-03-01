// Copyright Auticus Studios


#include "Game/ModCalculations/MMC_ResistFortitude.h"
#include "Game/MetaliaAttributeSet.h"
#include <Characters/CombatInterface.h>

UMMC_ResistFortitude::UMMC_ResistFortitude()
{
	StaminaDefinition.AttributeToCapture = UMetaliaAttributeSet::GetStaminaAttribute();
	StaminaDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StaminaDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(StaminaDefinition);
}

float UMMC_ResistFortitude::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather the tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Stamina = 0.f;
	GetCapturedAttributeMagnitude(StaminaDefinition, Spec, EvaluationParameters, Stamina);
	Stamina = FMath::Max<float>(Stamina, 0.f);

	// note that STEPHEN uses GetSourceObject() here which returns null, but GetEffectCauser seems to work fine.  Here that is ok because
	// the effect causer should be the character itself anyway (the target i guess?)  There is also a GetInstigator	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetEffectCauser());

	UE_LOG(LogTemp, Warning, TEXT("I'm returning a stamina back: %f"), Stamina);
	return Stamina;

	// TODO: if using level based resistances, here is how we'd do it
	/*
	if (CombatInterface == nullptr)
	{
		return Stamina;
	}

	const int32 Level = CombatInterface->GetCharacterLevel_Implementation();
	return 80.f + (2.5f * Vigor) + (10.f * Level);
	*/
}