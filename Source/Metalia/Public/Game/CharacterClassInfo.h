// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;

/* Represents the base class and one which will be applied to enemies */
UENUM(BlueprintType)
enum class ECharacterBaseClass : uint8
{
	Controller,
	Metalimancer,
	Metalilyte,
	Ranger,
	Skirmisher, // barbarians, thieves
	Warrior
};

/* Represents the character class applied to players which correspond to a base class (for readability purposes) */
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Drummer,
	RhythmGuitar,
	LeadGuitar,
	Bass,
	Vocals,
	Synth
};

UENUM(BlueprintType)
enum class ECharacterSecondaryClass : uint8
{
	Minion,
	Standard,
	Elite,
	Boss
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
};

/**
 * Data Asset housing information pertaining to character classes.
 */
UCLASS()
class METALIA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCharacterClassInfo();

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<ECharacterBaseClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(VisibleAnywhere, Category = "Character Class Mappings")
	TMap<ECharacterBaseClass, ECharacterClass> CharacterBaseClassToClassMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	/* A collection of abilities that all characters have */
	UPROPERTY(EditDefaultsOnly, Category = "Common Class Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

public:
	const FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterBaseClass CharacterClass);
	const ECharacterBaseClass GetBaseClassFromSpecificClass(ECharacterClass CharacterClass);
	const ECharacterClass GetCharacterClassFromBaseClass(ECharacterBaseClass CharacterClass);
};
