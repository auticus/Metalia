// Copyright Auticus Studios


#include "UI/Controllers/OverlayWidgetController.h"
#include "AttributeSet.h"
#include "Game/MetaliaAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	
	if (AttributeSet == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no AttributeSet"));
		return;
	}

	const UMetaliaAttributeSet* MetaliaAttributeSet = Cast<UMetaliaAttributeSet>(AttributeSet);
	if (MetaliaAttributeSet == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttributeSet could not be cast to MetaliaAttributeSet"));
		return;
	}

	OnHealthChanged.Broadcast(MetaliaAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MetaliaAttributeSet->GetMaxHealth());

	UE_LOG(LogTemp, Warning, TEXT("WidgetController is broadcasting initial values"));
}
