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
	/* Currently only used by enemies, the enemy class will call this to get its initial attributes */
	// This should only EVER be called by the server as clients do not have access to game mode
	AMetaliaGameMode* GM = Cast<AMetaliaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GM == nullptr)
	{
		// if this was coming from the client, GM is null
		return;
	}

	UCharacterClassInfo* CharacterClassInfo = GM->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	ApplyAttributeGameplayEffect(ClassDefaultInfo.PrimaryAttributes, Level, ASC);
	ApplyAttributeGameplayEffect(ClassDefaultInfo.SecondaryAttributes, Level, ASC);
	ApplyAttributeGameplayEffect(ClassDefaultInfo.VitalAttributes, Level, ASC);
	ApplyAttributeGameplayEffect(ClassDefaultInfo.ResistanceAttributes, Level, ASC);
}

void UMetaliaAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterBaseClass CharacterClass)
{
	AMetaliaGameMode* GM = Cast<AMetaliaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GM == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GiveStartupAbilities:: GameMode not found or not a Metalia Game Mode!"));
		return;
	}

	UCharacterClassInfo* CharacterClassInfo = GM->CharacterClassInfo;
	if (CharacterClassInfo == nullptr) return;

	// give the common abilities
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}

	// now grant startup abilities for that character class
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
	{
		const int CharacterLevel = CombatInterface->GetCharacterLevel_Implementation();

		for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CharacterLevel);
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

void UMetaliaAbilitySystemLibrary::GiveOnlyCommonAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	AMetaliaGameMode* GM = Cast<AMetaliaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GM == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GiveStartupAbilities:: GameMode not found or not a Metalia Game Mode!"));
		return;
	}

	UCharacterClassInfo* CharacterClassInfo = GM->CharacterClassInfo;
	if (CharacterClassInfo == nullptr) return;

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

void UMetaliaAbilitySystemLibrary::GetLivePlayersWithinRadius(
	const UObject* WorldContextObject, 
	TArray<AActor*>& OutOverlappingActors, 
	const TArray<AActor*>& ActorsToIgnore, 
	float Radius, 
	const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
			FCollisionShape::MakeSphere(Radius), SphereParams);

		for (FOverlapResult& Overlap : Overlaps)
		{
			if (!Overlap.GetActor()->Implements<UCombatInterface>() || ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				continue;
			}

			OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
		}
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

bool UMetaliaAbilitySystemLibrary::IsEnemy(AActor* FirstActor, AActor* SecondActor)
{
	const bool FirstIsPlayer = FirstActor->ActorHasTag(FName("Player"));
	const bool SecondIsPlayer = SecondActor->ActorHasTag(FName("Player"));

	return FirstIsPlayer != SecondIsPlayer;
}

bool UMetaliaAbilitySystemLibrary::IsTargetPlayerTagged(AActor* Target)
{
	return Target->ActorHasTag(FName("Player"));
}
