// Copyright Auticus Studios


#include "UI/Controllers/OverlayWidgetController.h"
#include "AttributeSet.h"
#include "Game/MetaliaAttributeSet.h"
#include <Game/MetaliaAbilitySystemComponent.h>

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
	OnMetalManaChanged.Broadcast(MetaliaAttributeSet->GetMetalMana());
	OnMaxMetalManaChanged.Broadcast(MetaliaAttributeSet->GetMaxMetalMana());

	UMetaliaAttributeSet* AS = CastChecked<UMetaliaAttributeSet>(AttributeSet);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UMetaliaAttributeSet* MetaliaAttributeSet = CastChecked<UMetaliaAttributeSet>(AttributeSet);
	
	/* LEAVING THIS HERE AS AN EXAMPLE
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetHealthAttribute()).AddUObject(
			this, 
			&UOverlayWidgetController::HealthChanged);
	*/

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetMetalManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMetalManaChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetMaxMetalManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxMetalManaChanged.Broadcast(Data.NewValue);
			}
	);

	Cast<UMetaliaAbilitySystemComponent>(AbilitySystemComponent)->OnEffectAssetTagsChanged.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					OnMessageWidgetRowBroadcast.Broadcast(*Row); //*Row is dereference... taking the pointer and getting its raw value
				}				
			}
		}
	);
}