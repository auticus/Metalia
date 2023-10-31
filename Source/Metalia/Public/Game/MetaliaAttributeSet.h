// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MetaliaAttributeSet.generated.h"

/**
 * Attribute set for Metalia characters.
 */
UCLASS()
class METALIA_API UMetaliaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Primary Attributes")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Primary Attributes")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Metal, Category = "Primary Attributes")
	FGameplayAttributeData Metal;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMetal, Category = "Primary Attributes")
	FGameplayAttributeData MaxMetal;

public:
	UMetaliaAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Metal(const FGameplayAttributeData& OldMetal) const;

	UFUNCTION()
	void OnRep_MaxMetal(const FGameplayAttributeData& OldMaxMetal) const;
};
