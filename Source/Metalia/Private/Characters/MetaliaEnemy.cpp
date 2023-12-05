// Copyright Auticus Studios


#include "Characters/MetaliaEnemy.h"
#include "Metalia/Metalia.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include <Game/MetaliaAbilitySystemComponent.h>

AMetaliaEnemy::AMetaliaEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

void AMetaliaEnemy::HighlightActor()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_STENCIL_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_STENCIL_RED);
}

void AMetaliaEnemy::UnhighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AMetaliaEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AMetaliaEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	// there is currently nothing set here and this will cause it to crash if you use it on the enemy.
	// Cast<UMetaliaAbilitySystemComponent>(AbilitySystemComponent)->Initialize();
}
