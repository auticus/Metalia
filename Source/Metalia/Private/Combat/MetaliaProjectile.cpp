// Copyright Auticus Studios


#include "Combat/MetaliaProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"

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
	SetLifeSpan(ProjectileLifeSpan);

	// spawn the sound that will play while the object is flying through the air
	InFlightSoundComponent = UGameplayStatics::SpawnSoundAttached(InFlightSound, GetRootComponent());
}

void AMetaliaProjectile::OnOverlap(AActor* TargetActor)
{
	HandleProjectileDestroyed();

	// if on the server, we have hit something, so destroy
	if (HasAuthority())
	{
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
		/*
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Destroyed calling HandleProjectileDestroyed()"));
		}
		*/

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