// Copyright Auticus Studios


#include "Characters/MetaliaCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include <AbilitySystemComponent.h>
#include <Game/MetaliaAttributeSet.h>
#include <Game/MetaliaAbilitySystemComponent.h>
#include <Player/MetaliaPlayerState.h>
#include <Metalia/Metalia.h>

// Sets default values
AMetaliaCharacterBase::AMetaliaCharacterBase()
{
 	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// set the character up so it is not blocking the camera and causing strange weirdness with camera zooming in
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// make sure only the character mesh generates overlap, not its capsule.  This does not stop blocking from occurring but rather
	// any code that uses overlap events to generate hits will ignore the capsule.
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void AMetaliaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AMetaliaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

int32 AMetaliaCharacterBase::GetCharacterLevel_Implementation() const
{
	return Level;
}

void AMetaliaCharacterBase::InitAbilityActorInfo()
{
	//does nothing in the base
}

void AMetaliaCharacterBase::InitializeDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultAttributeInitialization, 1.f);
}

void AMetaliaCharacterBase::InitializeDelegateBroadcastersAndBroadcastDefaults()
{
	// the base will currently do nothing and needs overridden
}

void AMetaliaCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float EffectLevel)
{
	UAbilitySystemComponent* abilitySystemComponent = GetAbilitySystemComponent();
	UObject* boxedComponent = Cast<UObject>(abilitySystemComponent);
	check(IsValid(boxedComponent));
	check(GameplayEffectClass);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, EffectLevel, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AMetaliaCharacterBase::AddCharacterAbilities()
{
	UMetaliaAbilitySystemComponent* ASC = CastChecked<UMetaliaAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	ASC->AddCharacterAbilities(StartupAbilities);
}

FVector AMetaliaCharacterBase::GetProjectileSocketLocation_Implementation()
{
	check(Weapon); // there should always be some kind of weapon
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

FRotator AMetaliaCharacterBase::GetProjectileSocketForwardRotation_Implementation()
{
	check(Weapon);
	return Weapon->GetForwardVector().Rotation();
}
