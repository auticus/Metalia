// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "MetaliaPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * Metalia's Player State component.
 */
UCLASS()
class METALIA_API AMetaliaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	AMetaliaPlayerState();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
