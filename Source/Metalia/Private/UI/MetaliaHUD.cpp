// Copyright Auticus Studios


#include "UI/MetaliaHUD.h"
#include "UI/View/MetaliaUIWidget.h"
#include "UI/Controllers/OverlayWidgetController.h"
#include "UI/Controllers/AttributeMenuWidgetController.h"

void AMetaliaHUD::BeginPlay()
{
	Super::BeginPlay();

}

void AMetaliaHUD::InitializeOverlay(FWidgetControllerParams params)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out the HUD blueprint"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out the HUD blueprint"));
	checkf(AttributeMenuWidgetControllerClass, TEXT("Attribute Menu Widget Controller Class uninitialized, please fill out the HUD blueprint"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UMetaliaUIWidget>(Widget);
	UOverlayWidgetController* Controller = GetOverlayWidgetController(params);
	OverlayWidget->SetWidgetController(Controller);
	Controller->BroadcastInitialValues(); // moved this into the GetOverlayWidgetController space

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

UAttributeMenuWidgetController* AMetaliaHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}

	return AttributeMenuWidgetController;
}
