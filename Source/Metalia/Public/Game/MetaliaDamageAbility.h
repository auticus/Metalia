// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Game/MetaliaGameplayAbility.h"
#include "MetaliaDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaDamageAbility : public UMetaliaGameplayAbility
{
	GENERATED_BODY()
	
protected:
	/* The Gameplay Effect that determines how damage is dealt by this projectile */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

};
