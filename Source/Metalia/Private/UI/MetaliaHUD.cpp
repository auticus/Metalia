// Copyright Auticus Studios


#include "UI/MetaliaHUD.h"
#include "UI/View/MetaliaUIWidget.h"

void AMetaliaHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}