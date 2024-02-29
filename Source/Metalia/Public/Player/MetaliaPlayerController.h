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
class UDamageTextComponent;
struct FGameplayTag;

/**
 * Main player controller.
 */
UCLASS()
class METALIA_API AMetaliaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

private:
	UPROPERTY(EditAnywhere, Category = "Input")
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

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMetaliaDataAsset> InputConfig;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

public:
	AMetaliaPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)  // client indicates its called on server but executed on client
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bIsBlocked, bool bIsCriticalHit);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	/* Moves the possessed actor */
	void Move(const struct FInputActionValue& InputActionValue);

	/* Responsible for tracing from the mouse cursor down to see what actors it hits */
	void CursorTrace();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UMetaliaAbilitySystemComponent* GetMetaliaAbilitySystemComponent();
};
