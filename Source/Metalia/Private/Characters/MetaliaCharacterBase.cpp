// Copyright Auticus Studios


#include "Characters/MetaliaCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include <AbilitySystemComponent.h>
#include <Game/MetaliaAttributeSet.h>
#include <Game/MetaliaAbilitySystemComponent.h>
#include <Player/MetaliaPlayerState.h>
#include <Metalia/Metalia.h>
#include <Kismet/KismetStringLibrary.h>

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

	BaseWalkSpeed = 350.f; // fairly slow speed
	bIsDead = false;
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
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
	ApplyEffectToSelf(DefaultAttributeInitialization, 1.f);
	ApplyEffectToSelf(DefaultResistanceAttributes, 1.f);
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

FVector AMetaliaCharacterBase::GetCombatSocketLocation_Implementation()
{
	check(Weapon); // there should always be some kind of weapon
	UE_LOG(LogTemp, Warning, TEXT("Getting socket %s"), WeaponTipSocketName);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

FRotator AMetaliaCharacterBase::GetCombatSocketForwardRotation_Implementation()
{
	check(Weapon);
	return Weapon->GetForwardVector().Rotation();
}

UAnimMontage* AMetaliaCharacterBase::GetHitReactMontage_Implementation()
{
	// in the future we will need parameters to know what direction we got hit at so we know what montage to send back but for now just send the front
	return HitReactMontage;
}

UAnimMontage* AMetaliaCharacterBase::GetDeathReactMontage_Implementation()
{
	return DeathReactMontage;
}

void AMetaliaCharacterBase::Die_Implementation(bool UseRagDollDeath)
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath_Implementation(UseRagDollDeath);
}

void AMetaliaCharacterBase::MulticastHandleDeath_Implementation(bool UseRagDollDeath)
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	if (UseRagDollDeath)
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetEnableGravity(true);
	}

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	SetActorTickEnabled(false);
	// SetActorEnableCollision(false); this makes him fall through the floor.

	Dissolve_Implementation();
	bIsDead = true;
}

bool AMetaliaCharacterBase::GetIsBlocking() const
{
	return bHitBlocking;
}

/* RPC Client call */
void AMetaliaCharacterBase::Dissolve_Implementation()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMaterial);
		StartDissolveTimeline(DynamicMaterial);
	}

	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMaterial);
		StartWeaponDissolveTimeline(DynamicMaterial);
	}
}

float AMetaliaCharacterBase::GetHealth_Implementation() const
{
	UMetaliaAttributeSet* AS = Cast<UMetaliaAttributeSet>(AttributeSet);
	return AS->GetHealth();
}

float AMetaliaCharacterBase::GetMaxHealth_Implementation() const
{
	UMetaliaAttributeSet* AS = Cast<UMetaliaAttributeSet>(AttributeSet);
	return AS->GetMaxHealth();
}

bool AMetaliaCharacterBase::IsDead_Implementation() const
{
	return bIsDead;
}

AActor* AMetaliaCharacterBase::GetAvatar_Implementation()
{
	return this;
}
