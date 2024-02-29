// Copyright Auticus Studios


#include "Game/Libraries/MetaliaAbilitySystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <UI/MetaliaHUD.h>
#include "UI/Controllers/MetaliaWidgetController.h"
#include <Player/MetaliaPlayerState.h>
#include <Game/MetaliaGameMode.h>
#include <GameplayEffectTypes.h>
#include "AbilitySystemComponent.h"
#include <Game/FAuraGameplayEffectContext.h>

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

void UMetaliaAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterBaseClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AMetaliaGameMode* GM = Cast<AMetaliaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GM == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeDefaultAttributes:: GameMode not found or not a Metalia Game Mode!"));
		return;
	}

	UCharacterClassInfo* CharacterClassInfo = GM->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	ApplyAttributeGameplayEffect(ClassDefaultInfo.PrimaryAttributes, Level, ASC);
	ApplyAttributeGameplayEffect(ClassDefaultInfo.SecondaryAttributes, Level, ASC);
	ApplyAttributeGameplayEffect(ClassDefaultInfo.VitalAttributes, Level, ASC);
}

void UMetaliaAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	AMetaliaGameMode* GM = Cast<AMetaliaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GM == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GiveStartupAbilities:: GameMode not found or not a Metalia Game Mode!"));
		return;
	}

	UCharacterClassInfo* CharacterClassInfo = GM->CharacterClassInfo;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

bool UMetaliaAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* EffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return EffectContext->IsBlockedHit();
	}
	return false;
}

bool UMetaliaAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* EffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return EffectContext->IsCriticalHit();
	}
	return false;
}

void UMetaliaAbilitySystemLibrary::SetIsBlockedHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool IsBlockedHit)
{
	if (FAuraGameplayEffectContext* EffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		EffectContext->SetIsBlockedHit(IsBlockedHit);
	}
}

void UMetaliaAbilitySystemLibrary::SetIsCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool IsCriticalHit)
{
	if (FAuraGameplayEffectContext* EffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		EffectContext->SetIsCriticalHit(IsCriticalHit);
	}
}

void UMetaliaAbilitySystemLibrary::ApplyAttributeGameplayEffect(TSubclassOf<UGameplayEffect> AttributeClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	FGameplayEffectContextHandle AttributeContextHandle = ASC->MakeEffectContext();
	AttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(AttributeClass, Level, AttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

