// Copyright Auticus Studios


#include "Game/MetaliaAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include <AbilitySystemBlueprintLibrary.h>

UMetaliaAttributeSet::UMetaliaAttributeSet()
{
}

void UMetaliaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/* This is the area where we register our variables for replication*/
	/* Look up the various conditions and when to notify.  In this case we will always notify so that
	*  we can get notified by server when any attempt came to change it, even if the values are the same */
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, MetalMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMetaliaAttributeSet, MaxMetalMana, COND_None, REPNOTIFY_Always);
}

void UMetaliaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// this override is good for just clamping values

	Super::PreAttributeChange(Attribute, NewValue);

	// Note that these clamps are only clamping the value of NewValue... GAS will still be working with the pre-adjusted values
	// which may cause you bugs.
	float MaxHealthScore = GetMaxHealth() > 0 ? GetMaxHealth() : DefaultVitalityScore;
	float MaxMetalManaScore = GetMaxMetalMana() > 0 ? GetMaxMetalMana() : DefaultVitalityScore;

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, MaxHealthScore);
	}
	else if (Attribute == GetMetalManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, MaxMetalManaScore);
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

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, MaxHealthScore));
	}
	if (Data.EvaluatedData.Attribute == GetMetalManaAttribute())
	{
		SetMetalMana(FMath::Clamp(GetMetalMana(), 0.f, MaxMetalManaScore));
	}

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

void UMetaliaAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Intelligence, OldIntelligence);
}

void UMetaliaAttributeSet::OnRep_Willpower(const FGameplayAttributeData& OldWillpower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Willpower, OldWillpower);
}

void UMetaliaAttributeSet::OnRep_Metal(const FGameplayAttributeData& OldMetal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Metal, OldMetal);
}
