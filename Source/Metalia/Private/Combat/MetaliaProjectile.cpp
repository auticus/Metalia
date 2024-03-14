// Copyright Auticus Studios


#include "Combat/MetaliaProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include <Components/BoxComponent.h>
#include <Components/CapsuleComponent.h>
#include <Metalia/Metalia.h>
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystemComponent.h"
#include "Game/MetaliaDamageAbility.h"

// Sets default values
AMetaliaProjectile::AMetaliaProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called every frame
void AMetaliaProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AMetaliaProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetCollisionChannelToProjectile();
	SetLifeSpan(ProjectileLifeSpan);

	// spawn the sound that will play while the object is flying through the air
	InFlightSoundComponent = UGameplayStatics::SpawnSoundAttached(InFlightSound, GetRootComponent());
}

void AMetaliaProjectile::SetCollisionChannelToProjectile()
{
	// because the collision objects are set in the blueprint we do not hardcode them here.
	// as such we need to be able to find it and make sure its set to the projectile channel

	TArray<USceneComponent*> Components;
	GetComponents<USceneComponent>(Components);
	
	for (auto* Component : Components)
	{
		if (USphereComponent* Sphere = Cast<USphereComponent>(Component))
		{
			if (Sphere->GetCollisionObjectType() != ECC_Projectile)
			{
				UE_LOG(LogTemp, Warning, TEXT("Projectile %s had its sphere component set to Projectile as it was set to something else"), *GetActorNameOrLabel());
				Sphere->SetCollisionObjectType(ECC_Projectile);
			}
		}
		if (UBoxComponent* Box = Cast<UBoxComponent>(Component))
		{
			if (Box->GetCollisionObjectType() != ECC_Projectile)
			{
				UE_LOG(LogTemp, Warning, TEXT("Projectile %s had its box component set to Projectile as it was set to something else"), *GetActorNameOrLabel());
				Box->SetCollisionObjectType(ECC_Projectile);
			}
		}
		if (UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Component))
		{
			if (Capsule->GetCollisionObjectType() != ECC_Projectile)
			{
				UE_LOG(LogTemp, Warning, TEXT("Projectile %s had its capsule component set to Projectile as it was set to something else"), *GetActorNameOrLabel());
				Capsule->SetCollisionObjectType(ECC_Projectile);
			}
		}
	}
}

void AMetaliaProjectile::OnOverlap(AActor* TargetActor)
{
	// Projectiles are always active unlike melee weapons which activate as they are swinging and deactivate after.
	HandleProjectileDestroyed();

	// if on the server, we have hit something, so destroy
	if (HasAuthority())
	{
		// apply the effect of the projectile onto the target, but only on the server
		// damage will be replicated and make its way to the client on its own
		AssignedDamageAbility->CauseDamage_Implementation(TargetActor);
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

void AMetaliaProjectile::OnEndOverlap(AActor* TargetActor)
{

}

void AMetaliaProjectile::Destroyed()
{
	// for client/server replication, if we have not yet hit and we do not have authority that means we are a client being told to destroy
	// this also means we haven't fired off our destroy effects so do that now
	if (!bHit && !HasAuthority())
	{
		HandleProjectileDestroyed();
	}
	Super::Destroyed();
}

void AMetaliaProjectile::HandleProjectileDestroyed()
{
	// when a projectile strikes something, play its impact sound and then produce its impact effect
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	if (InFlightSoundComponent)
	{
		InFlightSoundComponent->Stop();
	}
}