// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MetaliaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * Main player controller.
 */
UCLASS()
class METALIA_API AMetaliaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMetaliaPlayerController();

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

	void Move(const struct FInputActionValue& InputActionValue);
};
