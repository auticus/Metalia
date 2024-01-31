// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "MetaliaDataAsset.generated.h"

USTRUCT (BlueprintType)
struct FMetaliaInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMetaliaInputAction> AbilityInputActions;

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag) const;
};
