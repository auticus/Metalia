// Copyright Auticus Studios


#include "Game/MetaliaAttributeSet.h"
#include "Net/UnrealNetwork.h"

UMetaliaAttributeSet::UMetaliaAttributeSet()
{
	// init functions stem from the macro defined in the h file
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMetalMana(50.f);
	InitMaxMetalMana(50.f);
	UE_LOG(LogTemp, Warning, TEXT("Attribute Set Initialized"));
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

void UMetaliaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, Health, OldHealth);
}

void UMetaliaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, MaxHealth, OldMaxHealth);
}

void UMetaliaAttributeSet::OnRep_Metal(const FGameplayAttributeData& OldMetal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, MetalMana, OldMetal);
}

void UMetaliaAttributeSet::OnRep_MaxMetal(const FGameplayAttributeData& OldMaxMetal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMetaliaAttributeSet, MaxMetalMana, OldMaxMetal);
}
