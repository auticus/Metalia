// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystemComponent.h"
#include "AttributeInfo.generated.h"


USTRUCT(BlueprintType)
struct FMetaliaAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * 
 */
UCLASS()
class METALIA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FMetaliaAttributeInfo FindAttributeInfoFromTag(const FGameplayTag& Tag, bool bLogNotFound) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMetaliaAttributeInfo> AttributeInformation;
};
