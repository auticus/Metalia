// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MetaliaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UMetaliaDataAsset;
class UMetaliaAbilitySystemComponent;
struct FGameplayTag;

/**
 * Main player controller.
 */
UCLASS()
class METALIA_API AMetaliaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMetaliaPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> MetaliaPlayerContext;

	UPROPERTY()
	TObjectPtr<UMetaliaAbilitySystemComponent> MetaliaAbilitySystemComponent;
	
	/* NOTE - we have move action here but any actions dealing with ability system component are dealt with in that class */

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	
	/* The tolerance level of the game pad dead zone.  The higher the value, the more drift will be ignored.*/
	UPROPERTY(EditAnywhere, Category = "Input")
	float GamepadDeadZone;

	//TObjectPtr<IEnemyInterface> LastEnemy;
	//TObjectPtr<IEnemyInterface> CurrentEnemy;
	TScriptInterface<IEnemyInterface> LastEnemy;
	TScriptInterface<IEnemyInterface> CurrentEnemy;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UMetaliaDataAsset> InputConfig;

	/* Moves the possessed actor */
	void Move(const struct FInputActionValue& InputActionValue);

	/* Responsible for tracing from the mouse cursor down to see what actors it hits */
	void CursorTrace();

	/* Creates the HUD for the player interface */
	void CreateHud();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UMetaliaAbilitySystemComponent* GetMetaliaAbilitySystemComponent();
};
