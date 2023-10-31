// Copyright Auticus Studios


#include "Characters/MetaliaCharacterBase.h"

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
