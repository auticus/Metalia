// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaliaEffectActor.generated.h"

class USphereComponent;

UCLASS()
class METALIA_API AMetaliaEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetaliaEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> EffectMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> EffectSphere;

};
