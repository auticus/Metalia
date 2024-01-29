// Copyright Auticus Studios


#include "Game/Libraries/MetaliaAbilitySystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <UI/MetaliaHUD.h>
#include "UI/Controllers/MetaliaWidgetController.h"
#include <Player/MetaliaPlayerState.h>

UOverlayWidgetController* UMetaliaAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMetaliaHUD* HUD = Cast<AMetaliaHUD>(PC->GetHUD()))
		{
			AMetaliaPlayerState* PS = PC->GetPlayerState<AMetaliaPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams Params (PC, PS, ASC, AS);
			return HUD->GetOverlayWidgetController(Params);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UMetaliaAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMetaliaHUD* HUD = Cast<AMetaliaHUD>(PC->GetHUD()))
		{
			AMetaliaPlayerState* PS = PC->GetPlayerState<AMetaliaPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			
			const FWidgetControllerParams Params(PC, PS, ASC, AS);
			return HUD->GetAttributeMenuWidgetController(Params);
		}
	}

	return nullptr;
}
