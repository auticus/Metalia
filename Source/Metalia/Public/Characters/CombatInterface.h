// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface involving anything requiring combat data.
 */
class METALIA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetProjectileSocketLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FRotator GetProjectileSocketForwardRotation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage(); //TODO: where did you hit me?

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetDeathReactMontage();

	/* Kills the character, dropping their weapon(s) and if RagDollDeath is TRUE will RagDoll Death the character */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die(bool UseRagDollDeath);
};
