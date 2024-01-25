// Copyright Auticus Studios


#include "UI/Controllers/AttributeMenuWidgetController.h"
#include "MetaliaGameplayTags.h"
#include <Game/MetaliaAttributeSet.h>
#include "Game/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UMetaliaAttributeSet* AS = CastChecked<UMetaliaAttributeSet>(AttributeSet);
	check(AttributeInfo);

	FMetaliaAttributeInfo Info = AttributeInfo->FindAttributeInfoFromTag(FMetaliaGameplayTags::Get().Attributes_Primary_Strength, true);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}
