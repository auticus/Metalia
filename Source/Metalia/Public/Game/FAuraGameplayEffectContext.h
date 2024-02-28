// Copyright Auticus Studios

#pragma once

#include "GameplayEffectTypes.h"
#include "FAuraGameplayEffectContext.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }

	void SetIsCriticalHit(bool bIsCrit) { bIsCriticalHit = bIsCrit; }
	void SetIsBlockedHit(bool bIsBlocked) { bIsBlockedHit = bIsBlocked; }

	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;
};
