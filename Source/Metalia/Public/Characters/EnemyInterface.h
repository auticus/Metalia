// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface applied to actors that can be targeted.
 */
class METALIA_API IEnemyInterface
{
	GENERATED_BODY()

public:
	/* Highlight the actor that implements this interface */
	virtual void HighlightActor() = 0;

	/* Unhighlight the actor that implements this interface */
	virtual void UnhighlightActor() = 0;
};
