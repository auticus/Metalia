// Copyright Auticus Studios


#include "Characters/MetaliaEnemy.h"
#include "Metalia/Metalia.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

AMetaliaEnemy::AMetaliaEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

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