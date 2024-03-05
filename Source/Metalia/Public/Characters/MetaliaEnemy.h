// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/MetaliaCharacterBase.h"
#include "Characters/EnemyInterface.h"
#include "UI/Controllers/OverlayWidgetController.h" // for FOnAttributeChangedSignature - not a fan of it being in this file
#include "Game/CharacterClassInfo.h"
#include "BehaviorTree/BehaviorTree.h"
#include <AI/MetaliaAIController.h>
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float LifeTimeAfterDeath;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Combat")
	bool bWieldsRangedWeapon;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> Healthbar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterBaseClass CharacterClass = ECharacterBaseClass::Warrior;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AMetaliaAIController> MetaliaAIController;

public:
	/** Enemy Interface functions */
	/* Highlight the actor that implements this interface */
	void HighlightActor() override;

	/* Unhighlight the actor that implements this interface */
	void UnhighlightActor() override;
	/** END Enemy Interface functions */

	virtual void Die_Implementation(bool UseRagDollOnDeath) override;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController);
	virtual void InitializeDelegateBroadcastersAndBroadcastDefaults() override;
	virtual void InitializeDefaultAttributes() override;

private:
	void InitAbilityActorInfo() override;
};
