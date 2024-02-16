// Copyright Auticus Studios


#include "Characters/MetaliaEnemy.h"
#include "Metalia/Metalia.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include <Game/MetaliaAbilitySystemComponent.h>
#include <Game/MetaliaAttributeSet.h>
#include "Components/WidgetComponent.h"
#include "UI/View/MetaliaUIWidget.h"

AMetaliaEnemy::AMetaliaEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UMetaliaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMetaliaAttributeSet>("AttributeSet");

	Healthbar = CreateDefaultSubobject<UWidgetComponent>("Healthbar");
	Healthbar->SetupAttachment(GetRootComponent());
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

	if (UMetaliaUIWidget* HealthBarWidget = Cast<UMetaliaUIWidget>(Healthbar->GetUserWidgetObject()))
	{
		HealthBarWidget->SetWidgetController(this);
	}

	InitializeDelegateBroadcastersAndBroadcastDefaults();
}

void AMetaliaEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMetaliaAbilitySystemComponent>(AbilitySystemComponent)->Initialize();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

void AMetaliaEnemy::InitializeDelegateBroadcastersAndBroadcastDefaults()
{
	// currently no reason to call SUPER on this override as it does nothing
	UMetaliaAttributeSet* AS = Cast<UMetaliaAttributeSet>(AttributeSet);
	if (!AS)
	{
		UE_LOG(LogTemp, Warning, TEXT("MetaliaEnemy::InitializeDelegateBroadcasters - Attribute Set was not able to be cast to the appropriate value!  Delegates not bound"));
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	// Broadcast the initial default values
	OnHealthChanged.Broadcast(AS->GetHealth());
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
}
