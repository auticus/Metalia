// Copyright Auticus Studios


#include "Game/MetaliaEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectTypes.h"

// Sets default values
AMetaliaEffectActor::AMetaliaEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AMetaliaEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMetaliaEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetSystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetSystem == nullptr) return;

	check(GameplayEffectClass);

	float AbilityLevel = 1.f;
	FGameplayEffectContextHandle EffectContextHandle = TargetSystem->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetSystem->MakeOutgoingSpec(GameplayEffectClass, AbilityLevel, EffectContextHandle);
	const FActiveGameplayEffectHandle EffectHandle = TargetSystem->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()); // the * dereferences this to the object

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteGameplayApplicationEndPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(EffectHandle, TargetSystem);
	}
}

void AMetaliaEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffectClass && InstantGameplayApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationGameplayEffectClass && DurationGameplayApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteGameplayEffectClass && InfiniteGameplayApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AMetaliaEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffectClass && InstantGameplayApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationGameplayEffectClass && DurationGameplayApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteGameplayEffectClass && InfiniteGameplayApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteGameplayApplicationEndPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		RemoveInfiniteEffects(TargetActor);
	}
}

void AMetaliaEffectActor::RemoveInfiniteEffects(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC)) return;

	TArray<FActiveGameplayEffectHandle> HandlesToTerminate;
	for (auto HandledPair : ActiveEffectHandles)
	{
		if (TargetASC == HandledPair.Value)
		{
			const int StacksToRemove = 1;
			TargetASC->RemoveActiveGameplayEffect(HandledPair.Key, StacksToRemove);
			HandlesToTerminate.Add(HandledPair.Key);
		}
	}

	for (auto HastaLavista : HandlesToTerminate)
	{
		ActiveEffectHandles.FindAndRemoveChecked(HastaLavista);
	}
}
