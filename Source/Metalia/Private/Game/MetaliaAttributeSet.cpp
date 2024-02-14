// Copyright Auticus Studios


#include "Game/MetaliaAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "MetaliaGameplayTags.h"
#include <AbilitySystemBlueprintLibrary.h>

UMetaliaAttributeSet::UMetaliaAttributeSet()
{
	AttributeSetId = FGuid::NewGuid();
	AddPrimaryAttributesToMap();
	AddSecondaryAttributesToMap();
}

void UMetaliaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/* This is the area where we register our variables for replication*/
	/* Look up the various conditions and when to notify.  In this case we will always notify so that
	*  we can get notified by server when any attempt came to change it, even if the values are the same */

	/* Primary Attributes */
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Agility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Metal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Willpower, COND_None, REPNOTIFY_Always);

	/* Secondary Attributes*/
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Block, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, CarryCapacity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Critical, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, CriticalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, DamageModifier, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Fortitude, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, MetalManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Resolve, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Speed, COND_None, REPNOTIFY_Always);

	/* Vital Attributes */
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, MetalMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, MaxMetalMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Fatigue, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, MaxFatigue, COND_None, REPNOTIFY_Always);
}

void UMetaliaAttributeSet::AddPrimaryAttributesToMap()
{
	const FMetaliaGameplayTags& GameplayTags = FMetaliaGameplayTags::Get();

	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Agility, GetAgilityAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Stamina, GetStaminaAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Metal, GetMetalAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Will, GetWillpowerAttribute);
}

void UMetaliaAttributeSet::AddSecondaryAttributesToMap()
{
	const FMetaliaGameplayTags& GameplayTags = FMetaliaGameplayTags::Get();

	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Block, GetBlockAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_CarryCapacity, GetCarryCapacityAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Critical, GetCriticalAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_CriticalDamage, GetCriticalDamageAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_DamageModifier, GetDamageModifierAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Defense, GetDefenseAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Fortitude, GetFortitudeAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_HealthRegen, GetHealthRegenAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_ManaRegen, GetMetalManaRegenAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Resolve, GetResolveAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Speed, GetSpeedAttribute);
}

void UMetaliaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// this override is good for just clamping values

	Super::PreAttributeChange(Attribute, NewValue);

	// Note that these clamps are only clamping the value of NewValue... GAS will still be working with the pre-adjusted values
	// which may cause you bugs.
	float MaxHealthScore = GetMaxHealth() > 0 ? GetMaxHealth() : DefaultVitalityScore;
	float MaxMetalManaScore = GetMaxMetalMana() > 0 ? GetMaxMetalMana() : DefaultVitalityScore;
	float MaxFatigueScore = GetMaxFatigue() > 0 ? GetMaxFatigue() : DefaultVitalityScore;

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, MaxHealthScore);
	}
	else if (Attribute == GetMetalManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, MaxMetalManaScore);
	}
	else if (Attribute == GetFatigueAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, MaxFatigueScore);
	}
}

void UMetaliaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// this override is good for applying processing logic to attribute changes
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	// because the data used by GAS may break our clamp, we have to clamp it after its been changed
	float MaxHealthScore = GetMaxHealth() > 0 ? GetMaxHealth() : DefaultVitalityScore;
	float MaxMetalManaScore = GetMaxMetalMana() > 0 ? GetMaxMetalMana() : DefaultVitalityScore;
	float MaxFatigueScore = GetMaxFatigue() > 0 ? GetMaxFatigue() : DefaultVitalityScore;

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, MaxHealthScore));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *Props.TargetActor->GetName(), GetHealth());
	}
	if (Data.EvaluatedData.Attribute == GetMetalManaAttribute())
	{
		SetMetalMana(FMath::Clamp(GetMetalMana(), 0.f, MaxMetalManaScore));
	}
	if (Data.EvaluatedData.Attribute == GetFatigueAttribute())
	{
		SetFatigue(FMath::Clamp(GetFatigue(), 0.f, MaxFatigueScore));
	}
}

void UMetaliaAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	// source is the cause of the effect.  Target is likely us here.
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceComponent = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceComponent) && Props.SourceComponent->AbilityActorInfo.IsValid() && Props.SourceComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceActor = Props.SourceComponent->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceComponent->AbilityActorInfo->PlayerController.Get();

		// if i wasn't able to grab the controller from the actor, then lets cast it down to a pawn and get it that way
		if (Props.SourceController == nullptr && Props.SourceActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetActor);
		Props.TargetComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetActor);
	}

	// UE_LOG(LogTemp, Warning, TEXT("Strength is now: %f"), GetStrength());
}

void UMetaliaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Health, OldHealth);
}

void UMetaliaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, MaxHealth, OldMaxHealth);
}

void UMetaliaAttributeSet::OnRep_MetalMana(const FGameplayAttributeData& OldMetalMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, MetalMana, OldMetalMana);
}

void UMetaliaAttributeSet::OnRep_MaxMetalMana(const FGameplayAttributeData& OldMaxMetalMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, MaxMetalMana, OldMaxMetalMana);
}

void UMetaliaAttributeSet::OnRep_MaxFatigue(const FGameplayAttributeData& OldMaxFatigue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, MaxFatigue, OldMaxFatigue);
}

void UMetaliaAttributeSet::OnRep_Fatigue(const FGameplayAttributeData& OldFatigue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Fatigue, OldFatigue);
}

void UMetaliaAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Strength, OldStrength);
}

void UMetaliaAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Agility, OldAgility);
}

void UMetaliaAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Stamina, OldStamina);
}

void UMetaliaAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Vigor, OldVigor);
}

void UMetaliaAttributeSet::OnRep_Willpower(const FGameplayAttributeData& OldWillpower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Willpower, OldWillpower);
}

void UMetaliaAttributeSet::OnRep_Metal(const FGameplayAttributeData& OldMetal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Metal, OldMetal);
}

void UMetaliaAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UMetaliaAttributeSet::OnRep_Block(const FGameplayAttributeData& OldBlock) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Block, OldBlock);
}

void UMetaliaAttributeSet::OnRep_CarryCapacity(const FGameplayAttributeData& OldCarryCapacity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, CarryCapacity, OldCarryCapacity);
}

void UMetaliaAttributeSet::OnRep_Critical(const FGameplayAttributeData& OldCritical) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Critical, OldCritical);
}

void UMetaliaAttributeSet::OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, CriticalDamage, OldCriticalDamage);
}

void UMetaliaAttributeSet::OnRep_DamageModifier(const FGameplayAttributeData& OldDamageModifier) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, DamageModifier, OldDamageModifier);
}

void UMetaliaAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Defense, OldDefense);
}

void UMetaliaAttributeSet::OnRep_Fortitude(const FGameplayAttributeData& OldFortitude) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Fortitude, OldFortitude);
}

void UMetaliaAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, HealthRegen, OldHealthRegen);
}

void UMetaliaAttributeSet::OnRep_MetalManaRegen(const FGameplayAttributeData& OldMetalManaRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, MetalManaRegen, OldMetalManaRegen);
}

void UMetaliaAttributeSet::OnRep_Resolve(const FGameplayAttributeData& OldResolve) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Resolve, OldResolve);
}

void UMetaliaAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Speed, OldSpeed);
}
