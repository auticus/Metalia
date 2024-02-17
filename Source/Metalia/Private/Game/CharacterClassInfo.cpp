// Copyright Auticus Studios


#include "Game/CharacterClassInfo.h"

UCharacterClassInfo::UCharacterClassInfo()
{
	CharacterBaseClassToClassMapping.Add(ECharacterBaseClass::Warrior, ECharacterClass::Drummer);
	CharacterBaseClassToClassMapping.Add(ECharacterBaseClass::Ranger, ECharacterClass::RhythmGuitar);
	CharacterBaseClassToClassMapping.Add(ECharacterBaseClass::Metalimancer, ECharacterClass::LeadGuitar);
	CharacterBaseClassToClassMapping.Add(ECharacterBaseClass::Metalilyte, ECharacterClass::Bass);
	CharacterBaseClassToClassMapping.Add(ECharacterBaseClass::Controller, ECharacterClass::Vocals);
	CharacterBaseClassToClassMapping.Add(ECharacterBaseClass::Skirmisher, ECharacterClass::Synth);
}

const FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterBaseClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}

const ECharacterBaseClass UCharacterClassInfo::GetBaseClassFromSpecificClass(ECharacterClass CharacterClass)
{
	auto BaseClassKey = CharacterBaseClassToClassMapping.FindKey(CharacterClass);
	return *BaseClassKey;
}

const ECharacterClass UCharacterClassInfo::GetCharacterClassFromBaseClass(ECharacterBaseClass CharacterClass)
{
	return CharacterBaseClassToClassMapping.FindChecked(CharacterClass);
}
