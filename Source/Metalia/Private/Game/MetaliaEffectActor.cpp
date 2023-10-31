// Copyright Auticus Studios


#include "Game/MetaliaEffectActor.h"
#include "Components/SphereComponent.h"
#include <AbilitySystemInterface.h>
#include <Game/MetaliaAttributeSet.h>

// Sets default values
AMetaliaEffectActor::AMetaliaEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	EffectMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(EffectMesh);

	EffectSphere = CreateDefaultSubobject<USphereComponent>("EffectSphere");
	EffectSphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AMetaliaEffectActor::BeginPlay()
{
	Super::BeginPlay();

	EffectSphere->OnComponentBeginOverlap.AddDynamic(this, &AMetaliaEffectActor::OnOverlap);
	EffectSphere->OnComponentEndOverlap.AddDynamic(this, &AMetaliaEffectActor::EndOverlap);
}

void AMetaliaEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	/* ATTEMPTING TO READ THE ATTRIBUTE RESULTS IN ACCESS VIOLATION CRASH*/

	/*
	// the below is not the best way to do this - we have better ways we just dont know yet
	if (IAbilitySystemInterface* otherAbilitySystem = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UMetaliaAttributeSet* MetaliaAttributeSet = Cast<UMetaliaAttributeSet>(
			otherAbilitySystem->GetAbilitySystemComponent()->GetAttributeSet(UMetaliaAttributeSet::StaticClass()));
		
		// do the thing we shouldn't do and remove the const so we can change things directly
		UMetaliaAttributeSet* attributeSet = const_cast<UMetaliaAttributeSet*>(MetaliaAttributeSet);
		float currentHealth = MetaliaAttributeSet->GetHealth();
		attributeSet->SetHealth(currentHealth + 25.f);
		Destroy();
	}
	*/
	Destroy();
}

void AMetaliaEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

