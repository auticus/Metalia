// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MetaliaHUD.generated.h"

class UMetaliaUIWidget;

/**
 * 
 */
UCLASS()
class METALIA_API AMetaliaHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<UMetaliaUIWidget> OverlayWidget;
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMetaliaUIWidget> OverlayWidgetClass;

/* Functions */
protected:
	virtual void BeginPlay() override;
};
