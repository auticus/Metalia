// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Characters/CombatInterface.h"
#include "MetaliaPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * Metalia's Player State component.
 */
UCLASS()
class METALIA_API AMetaliaPlayerState : public APlayerState, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()
	
	AMetaliaPlayerState();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	FORCEINLINE int32 GetCharacterLevel() const override { return Level; }
};
