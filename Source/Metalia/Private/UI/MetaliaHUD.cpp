// Copyright Auticus Studios


#include "UI/MetaliaHUD.h"
#include "UI/View/MetaliaUIWidget.h"
#include "UI/Controllers/OverlayWidgetController.h"

void AMetaliaHUD::BeginPlay()
{
	Super::BeginPlay();

}

void AMetaliaHUD::InitializeOverlay(FWidgetControllerParams params)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out the HUD blueprint"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out the HUD blueprint"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UMetaliaUIWidget>(Widget);
	UOverlayWidgetController* Controller = GetOverlayWidgetController(params);
	OverlayWidget->SetWidgetController(Controller);
	Controller->BroadcastInitialValues();

	Widget->AddToViewport();
}

UOverlayWidgetController* AMetaliaHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}
