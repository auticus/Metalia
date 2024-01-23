// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "UI/Controllers/MetaliaWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class METALIA_API UAttributeMenuWidgetController : public UMetaliaWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
};
