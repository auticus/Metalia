// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaliaProjectile.generated.h"

class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class METALIA_API AMetaliaProjectile : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> InFlightSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> InFlightSoundComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

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

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void HandleProjectileDestroyed();
};
