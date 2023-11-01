// Copyright Auticus Studios


#include "UI/View/MetaliaUIWidget.h"

void UMetaliaUIWidget::SetWidgetController(UObject* InputController)
{
	WidgetController = InputController;
	WidgetControllerSet();
}
