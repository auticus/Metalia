// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/MetaliaCharacterBase.h"
#include "MetaliaCharacter.generated.h"

/**
 * Represents a playable Metalia character.
 */
UCLASS()
class METALIA_API AMetaliaCharacter : public AMetaliaCharacterBase
{
	GENERATED_BODY()
	
public:
	AMetaliaCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();
};
