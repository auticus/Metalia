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
		return StaticStruct();
	}

	virtual FAuraGameplayEffectContext* Duplicate() const
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;
};

// simply defining here is not enough we need to get this to be used project wide.
template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
