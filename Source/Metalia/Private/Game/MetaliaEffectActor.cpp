// Copyright Auticus Studios


#include "Game/MetaliaEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"

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
	TargetSystem->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()); // the * dereferences this to the object
}
