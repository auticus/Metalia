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

	UE_LOG(LogTemp, Warning, TEXT("WidgetController is broadcasting initial values, if you dont see your changes reflected look at BroadcastInitialValues()"));
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UMetaliaAttributeSet* MetaliaAttributeSet = CastChecked<UMetaliaAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetHealthAttribute()).AddUObject(
			this, 
			&UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetMaxHealthAttribute()).AddUObject(
			this,
			&UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetMetalManaAttribute()).AddUObject(
			this,
			&UOverlayWidgetController::MetalManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MetaliaAttributeSet->GetMaxMetalManaAttribute()).AddUObject(
			this,
			&UOverlayWidgetController::MaxMetalManaChanged);

	Cast<UMetaliaAbilitySystemComponent>(AbilitySystemComponent)->OnEffectAssetTagsChanged.AddLambda(
		[](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, Msg);
			}
		}
	);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MetalManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMetalManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxMetalManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxMetalManaChanged.Broadcast(Data.NewValue);
}