// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/MetaliaCharacterBase.h"
#include "Characters/EnemyInterface.h"
#include "UI/Controllers/OverlayWidgetController.h" // for FOnAttributeChangedSignature - not a fan of it being in this file
#include "MetaliaEnemy.generated.h"

class UWidgetComponent;

/**
 * Class applied to enemy characters.
 */
UCLASS()
class METALIA_API AMetaliaEnemy : public AMetaliaCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	AMetaliaEnemy();

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> Healthbar;

public:
	/** Enemy Interface functions */
	/* Highlight the actor that implements this interface */
	void HighlightActor() override;

	/* Unhighlight the actor that implements this interface */
	void UnhighlightActor() override;
	/** END Enemy Interface functions */

protected:
	virtual void BeginPlay() override;
	virtual void InitializeDelegateBroadcastersAndBroadcastDefaults() override;

private:
	void InitAbilityActorInfo() override;
};
