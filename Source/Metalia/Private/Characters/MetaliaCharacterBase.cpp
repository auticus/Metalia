// Copyright Auticus Studios


#include "Characters/MetaliaCharacterBase.h"
#include <AbilitySystemComponent.h>

// Sets default values
AMetaliaCharacterBase::AMetaliaCharacterBase()
{
 	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMetaliaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AMetaliaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMetaliaCharacterBase::InitAbilityActorInfo()
{
	//does nothing in the base
}

void AMetaliaCharacterBase::InitializePrimaryAttributes()
{
	UAbilitySystemComponent* abilitySystemComponent = GetAbilitySystemComponent();
	UObject* boxedComponent = Cast<UObject>(abilitySystemComponent);
	check(IsValid(boxedComponent));
	check(DefaultPrimaryAttributes);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}
