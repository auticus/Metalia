// Copyright Auticus Studios


#include "Characters/MetaliaEnemy.h"
#include "Metalia/Metalia.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include <Game/MetaliaAbilitySystemComponent.h>
#include <Game/MetaliaAttributeSet.h>
#include "Components/WidgetComponent.h"
#include "UI/View/MetaliaUIWidget.h"
#include <Game/Libraries/MetaliaAbilitySystemLibrary.h>
#include "MetaliaGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"

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

void AMetaliaEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();

	if (HasAuthority())
	{
		// only server should be giving startup abilities
		UMetaliaAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}

	if (UMetaliaUIWidget* HealthBarWidget = Cast<UMetaliaUIWidget>(Healthbar->GetUserWidgetObject()))
	{
		HealthBarWidget->SetWidgetController(this);
	}

	//bind any functions
	// note hit react tag only applies to enemies and that is why we put it here.
	AbilitySystemComponent->RegisterGameplayTagEvent(FMetaliaGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,
		&AMetaliaEnemy::HitReactTagChanged
	);

	InitializeDelegateBroadcastersAndBroadcastDefaults();
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
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	OnHealthChanged.Broadcast(AS->GetHealth());
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

void AMetaliaEnemy::InitializeDefaultAttributes()
{
	UMetaliaAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);

	// the vitals will initialize the max health, fatigue, and metal mana so now we need to just set the health to match those
	// enemies being initialized will always start at full health
	UMetaliaAttributeSet* AS = Cast<UMetaliaAttributeSet>(AttributeSet);
	AS->SetHealth(AS->GetMaxHealth());
	AS->SetMetalMana(AS->GetMaxMetalMana());
	AS->SetFatigue(AS->GetMaxFatigue());
}

void AMetaliaEnemy::Die_Implementation(bool UseRagDollOnDeath)
{
	SetLifeSpan(LifeTimeAfterDeath);
	Super::Die_Implementation(UseRagDollOnDeath);
}

void AMetaliaEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	// react to when a HitReact tag is added or removed from the enemy
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0 : BaseWalkSpeed;
}
