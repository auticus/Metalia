// Copyright Auticus Studios


#include "Game/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "Game/MetaliaAttributeSet.h"
#include "GameplayEffectAggregator.h"
#include "MetaliaGameplayTags.h"
#include "Game/Libraries/MetaliaAbilitySystemLibrary.h"
#include <Characters/MetaliaCharacterBase.h>

struct MetaliaDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Block);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Critical);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceFire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceLightning);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceFortitude);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceArcane);

	MetaliaDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, Block, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, Critical, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, CriticalDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, Defense, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, ResistanceFire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, ResistanceLightning, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, ResistanceFortitude, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMetaliaAttributeSet, ResistanceArcane, Target, false);
	}
};

static const MetaliaDamageStatics& DamageStatics()
{
	static MetaliaDamageStatics DStatics;  // as a static, everytime you call this, this same data will be here waiting
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	// in the constructor, add the definitions that we want to change
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().DefenseDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceFireDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceLightningDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceFortitudeDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceArcaneDef);

	GameplayTagToAttributeDefinitionMap.Add(FMetaliaGameplayTags::Get().Attributes_Resistance_Fire, DamageStatics().ResistanceFireDef);
	GameplayTagToAttributeDefinitionMap.Add(FMetaliaGameplayTags::Get().Attributes_Resistance_Arcane, DamageStatics().ResistanceArcaneDef);
	GameplayTagToAttributeDefinitionMap.Add(FMetaliaGameplayTags::Get().Attributes_Resistance_Lightning, DamageStatics().ResistanceLightningDef);
	GameplayTagToAttributeDefinitionMap.Add(FMetaliaGameplayTags::Get().Attributes_Resistance_Fortitude, DamageStatics().ResistanceFortitudeDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
													FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	// not every actor will be a metalia character so keep that in mind
	AMetaliaCharacterBase* TargetCharacterBase = TargetAvatar ? Cast<AMetaliaCharacterBase>(TargetAvatar) : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	// obtain the source and execute and perform our custom logic
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by the Caller Magnitude - how much damage is this guy doing?
	float Damage = 0.f;
	
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FMetaliaGameplayTags::Get().DamageTypesToResistanceMap)
	{
		// for every possible type of damage that we acknowledge, determine if there is any damage here
		// Key is the Damage Type, Value is the Resistance
		// Be AWARE: this loops through EVERY type of damage, which means items not even found
		// it also means this may be a performance pitfall and we may want to make it so its only looping through guaranteed items not ALL items

		Damage += ProcessDamageWithResistance(ExecutionParams, EvaluationParameters, Pair.Key, Pair.Value);
	}

	// TODO: its possible that blocking implements may have their own resistances that only pertain to when you block with them
	Damage = ProcessDamageAfterBlock(TargetCharacterBase, ExecutionParams, EvaluationParameters, Damage);
	Damage = ProcessDamageAfterDefense(ExecutionParams, EvaluationParameters, Damage);
	Damage = ProcessPotentialCriticalHit(ExecutionParams, EvaluationParameters, Damage);

	const FGameplayModifierEvaluatedData EvaluatedData(UMetaliaAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

float UExecCalc_Damage::ProcessDamageWithResistance(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters EvaluationParameters,
	const FGameplayTag DamageTag,
	const FGameplayTag ResistanceTag) const
{
	// potential performance hit having to pull spec each time
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	float Damage = Spec.GetSetByCallerMagnitude(DamageTag, false); // if not found it will log an error unless you tell it not to
	
	if (Damage == 0.0f) return 0.0f;

	float ResistanceValue = 0.f;
	checkf(GameplayTagToAttributeDefinitionMap.Contains(ResistanceTag), TEXT("ExecCalcDamage::ProcessDamageWithResistance Map Array does not contain tag [%s]"), *ResistanceTag.ToString());
	FGameplayEffectAttributeCaptureDefinition  ResistanceDefinition = GameplayTagToAttributeDefinitionMap[ResistanceTag];
		
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ResistanceDefinition, EvaluationParameters, ResistanceValue);
	ResistanceValue = FMath::Max<float>(ResistanceValue, 0.f);
	return Damage - (Damage * (ResistanceValue / 100.f));
}

float UExecCalc_Damage::ProcessDamageAfterBlock(
	AMetaliaCharacterBase* TargetCharacterBase,
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FAggregatorEvaluateParameters EvaluationParameters,
	float Damage) const
{
	float BlockedPercentage = 0.f;
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

	// If the target is listed in a blocking state we will negate some of the damage coming in by the Block value
	if (TargetCharacterBase && TargetCharacterBase->GetIsBlocking())
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockDef, EvaluationParameters, BlockedPercentage);
		BlockedPercentage = FMath::Max<float>(BlockedPercentage, 0.f);
		UMetaliaAbilitySystemLibrary::SetIsBlockedHit(ContextHandle, true);
	}
	else
	{
		UMetaliaAbilitySystemLibrary::SetIsBlockedHit(ContextHandle, false);
		return Damage;
	}

	return Damage - (Damage * (BlockedPercentage / 100.f));
}

float UExecCalc_Damage::ProcessDamageAfterDefense(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FAggregatorEvaluateParameters EvaluationParameters,
	float Damage) const
{
	// Defense
	float DefenseAbsorbedPercentage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DefenseDef, EvaluationParameters, DefenseAbsorbedPercentage);
	DefenseAbsorbedPercentage = FMath::Max<float>(DefenseAbsorbedPercentage, 0.f);

	// Armor penetration will remove some of this (to a min of 0)
	float ArmorPenetrationPercentage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, ArmorPenetrationPercentage);
	ArmorPenetrationPercentage = FMath::Max<float>(ArmorPenetrationPercentage, 0.f);

	// now adjust defense absorbed percentage by the armor penetration, to a min of 0
	DefenseAbsorbedPercentage = FMath::Max<float>(DefenseAbsorbedPercentage - ArmorPenetrationPercentage, 0.f);

	if (DefenseAbsorbedPercentage == 0.f) return Damage;
	return Damage - (Damage * (DefenseAbsorbedPercentage / 100.f));
}

float UExecCalc_Damage::ProcessPotentialCriticalHit(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FAggregatorEvaluateParameters EvaluationParameters,
	float Damage) const
{
	// TODO: this will likely need to pull from a curve table in the future
	// right now crit damage is hardcoded at 2.f (double damage) in the GameEffect.

	float CritHitPercent = 0.f;
	float CritHitMultiplier = 0.f;
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalDef, EvaluationParameters, CritHitPercent);
	CritHitPercent = FMath::Max<float>(CritHitPercent, 0.f);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalDamageDef, EvaluationParameters, CritHitMultiplier);
	CritHitMultiplier = FMath::Max<float>(CritHitMultiplier, 0.f);

	const bool bCritHit = FMath::RandRange(1, 100) < CritHitPercent;
	UMetaliaAbilitySystemLibrary::SetIsCriticalHit(ContextHandle, bCritHit);

	return bCritHit ? Damage *= CritHitMultiplier : Damage;
}
