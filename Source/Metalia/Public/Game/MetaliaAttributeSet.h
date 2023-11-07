// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MetaliaAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER (PropertyName)

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
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Primary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Metal, Category = "Primary Attributes")
	FGameplayAttributeData MetalMana;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, MetalMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMetal, Category = "Primary Attributes")
	FGameplayAttributeData MaxMetalMana;
	ATTRIBUTE_ACCESSORS(UMetaliaAttributeSet, MaxMetalMana);

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
