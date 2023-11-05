// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/MetaliaWidgetController.h"
#include "OverlayWidgetController.generated.h"

// want these to be broadcast in blueprints so they will be dynamic multicast
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS()
class METALIA_API UOverlayWidgetController : public UMetaliaWidgetController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

public:
	virtual void BroadcastInitialValues() override;
};
