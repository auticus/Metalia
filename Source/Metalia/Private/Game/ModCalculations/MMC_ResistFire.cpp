// Copyright Auticus Studios


#include "Game/ModCalculations/MMC_ResistFire.h"
#include "Game/MetaliaAttributeSet.h"
#include <Characters/CombatInterface.h>

UMMC_ResistFire::UMMC_ResistFire()
{
	
}

float UMMC_ResistFire::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// currently this will be impacted by abilities, items, etc.  
	// Defense is already modified by agility and that will also soak some of the damage, its not right
	// to soak it even more.

	return 0.f;
}
