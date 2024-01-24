// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MetaliaHUD.generated.h"

class UMetaliaUIWidget;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
struct FWidgetControllerParams;

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

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
	void InitializeOverlay(FWidgetControllerParams params);
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMetaliaUIWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf< UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	/* Attribute Menu Controller*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

/* Functions */
protected:
	virtual void BeginPlay() override;
};
