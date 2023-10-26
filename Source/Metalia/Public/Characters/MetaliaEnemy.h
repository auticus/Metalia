// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/MetaliaCharacterBase.h"
#include "Characters/EnemyInterface.h"
#include "MetaliaEnemy.generated.h"

/**
 * Class applied to enemy characters.
 */
UCLASS()
class METALIA_API AMetaliaEnemy : public AMetaliaCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	AMetaliaEnemy();

public:
	/* Highlight the actor that implements this interface */
	void HighlightActor() override;

	/* Unhighlight the actor that implements this interface */
	void UnhighlightActor() override;

};
