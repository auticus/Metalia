// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaliaProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class METALIA_API AMetaliaProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	AMetaliaProjectile();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
};
