// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/Weapon.h"
#include "GameplayEffectTypes.h" // struct so... includes it in the h instead of cpp
#include "MetaliaProjectile.generated.h"

class UProjectileMovementComponent;
class UNiagaraSystem;
class UGameplayEffect;

UCLASS()
class METALIA_API AMetaliaProjectile : public AWeapon
{
	GENERATED_BODY()
	
protected:
	/* The effect system to play when the projectile hits its target */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	/* The sound to play while the projectile is flying */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> InFlightSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> InFlightSoundComponent;

	/* Special impact sound like explosion - do not use armor or create impact sounds here those should be defined on the character itself */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
	/* End FX */

private:
	/* Bool that indicates if the projectile has already hit its target (for Client/Server replication) */
	bool bHit = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileLifeSpan = 10.f;

/* FUNCTIONS */
public:
	// Sets default values for this actor's properties
	AMetaliaProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Called when the object has been destroyed, useful for client/server checks */
	virtual void Destroyed() override;

	// already a UFUNCTION
	virtual void OnOverlap(AActor* TargetActor) override;

	// already a UFUNCTION
	virtual void OnEndOverlap(AActor* TargetActor) override;

	UFUNCTION(BlueprintCallable)
	void HandleProjectileDestroyed();

private:
	void SetCollisionChannelToProjectile();
};
