// Copyright Auticus Studios


#include "Game/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "Game/MetaliaAttributeSet.h"
#include "GameplayEffectAggregator.h"
#include "MetaliaGameplayTags.h"
#include <Characters/MetaliaCharacterBase.h>

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Block);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, Block, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, Defense, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;  // as a static, everytime you call this, this same data will be here waiting
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	// in the constructor, add the definitions that we want to change
	RelevantAttributesToCapture.Add(DamageStatics().BlockDef);
	RelevantAttributesToCapture.Add(DamageStatics().DefenseDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
													FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	// not every actor will be a metalia character so keep that in mind
	const AMetaliaCharacterBase* TargetCharacterBase = TargetAvatar ? Cast<AMetaliaCharacterBase>(TargetAvatar) : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// obtain the source and execute and perform our custom logic
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by the Caller Magnitude - how much damage is this guy doing?
	float Damage = Spec.GetSetByCallerMagnitude(FMetaliaGameplayTags::Get().Damage);

	float BlockedPercentage = 0.f;

	// If the target is listed in a blocking state we will negate some of the damage coming in by the Block value
	if (TargetCharacterBase && TargetCharacterBase->GetIsBlocking())
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockDef, EvaluationParameters, BlockedPercentage);
		BlockedPercentage = FMath::Max<float>(BlockedPercentage, 0.f);
	}

	Damage = Damage - (Damage * (BlockedPercentage / 100.f));

	const FGameplayModifierEvaluatedData EvaluatedData(UMetaliaAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
