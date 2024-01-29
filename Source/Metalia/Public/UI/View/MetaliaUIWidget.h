// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MetaliaUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UMetaliaUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InputController);

protected:
	/// <summary>
	/// Event that fires in response to SetWidgetController being fired.
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
