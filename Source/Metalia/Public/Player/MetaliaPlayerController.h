// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MetaliaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;

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
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> MetaliaPlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	/* The tolerance level of the game pad dead zone.  The higher the value, the more drift will be ignored.*/
	UPROPERTY(EditAnywhere, Category = "Input")
	float GamepadDeadZone;

	IEnemyInterface* LastEnemy;
	IEnemyInterface* CurrentEnemy;

	/* Moves the possessed actor */
	void Move(const struct FInputActionValue& InputActionValue);

	/* Responsible for tracing from the mouse cursor down to see what actors it hits */
	void CursorTrace();
};
