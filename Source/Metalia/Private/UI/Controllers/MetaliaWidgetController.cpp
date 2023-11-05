// Copyright Auticus Studios


#include "UI/Controllers/MetaliaWidgetController.h"

void UMetaliaWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& params)
{
	PlayerController = params.PlayerController;
	PlayerState = params.PlayerState;
	AbilitySystemComponent = params.AbilitySystemComponent;
	AttributeSet = params.AttributeSet;
}

void UMetaliaWidgetController::BroadcastInitialValues()
{
	
}
