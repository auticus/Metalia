// Copyright Auticus Studios


#include "Combat/MetaliaProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMetaliaProjectile::AMetaliaProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = InitialSpeed == 0.f ? 550.f : InitialSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed == 0.f ? 550.f : MaxSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AMetaliaProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMetaliaProjectile::OnOverlap(AActor* TargetActor)
{

}

void AMetaliaProjectile::OnEndOverlap(AActor* TargetActor)
{

}

// Called every frame
void AMetaliaProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

