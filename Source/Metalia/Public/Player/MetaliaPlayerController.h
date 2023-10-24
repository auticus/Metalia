// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MetaliaPlayerController.generated.h"

class UInputMappingContext;

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

private:

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> MetaliaPlayerContext;
};
