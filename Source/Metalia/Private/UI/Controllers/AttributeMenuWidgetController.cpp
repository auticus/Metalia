// Copyright Auticus Studios


#include "UI/Controllers/AttributeMenuWidgetController.h"
#include "MetaliaGameplayTags.h"
#include <Game/MetaliaAttributeSet.h>
#include "Game/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	UMetaliaAttributeSet* AS = CastChecked<UMetaliaAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& TagAttributePair : AS->TagsToAttributesMap)
	{
		BroadcastAttributeInfo(TagAttributePair.Key, TagAttributePair.Value());
	}

	UE_LOG(LogTemp, Warning, TEXT("AttributeMenuWidgetController::BroadcastInitialValues() runs"));
	AS->LogStrength();
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	UMetaliaAttributeSet* AS = CastChecked<UMetaliaAttributeSet>(AttributeSet);
	
	for (auto& TagAttributePair : AS->TagsToAttributesMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TagAttributePair.Value()).AddLambda(
			[this, TagAttributePair, AS](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(TagAttributePair.Key, TagAttributePair.Value());
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FMetaliaAttributeInfo Info = AttributeInfo->FindAttributeInfoFromTag(AttributeTag, true);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
