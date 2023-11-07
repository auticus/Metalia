// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaliaEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class METALIA_API AMetaliaEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetaliaEffectActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

private:
};
