// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include <Characters/CombatInterface.h>
#include "Items/Item.h"
#include "GameplayEffectTypes.h" // struct so... includes it in the h instead of cpp
#include "Weapon.generated.h"

/**
 * A weapon.
 */
UCLASS()
class METALIA_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();

public:
	/* The damage effect spec handle that will be used to cause the effect of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	/* The name of the socket on the character's skeletal mesh (set in blueprint) of the character that this weapon bonds to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meta, meta = (AllowPrivateAccess = "true"))
	FString SocketName;

	/* The name of the socket (set in blueprint) that holds the melee weapon when not equipped */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meta, meta = (AllowPrivateAccess = "true"))
	FString WeaponStowedSocketName;

	/* How many hands the weapon requires */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meta, meta = (AllowPrivateAccess = "true"))
	bool bRequiresTwoHands;

	/* How far the weapon can shoot (if at all) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meta, meta = (AllowPrivateAccess = "true"))
	int32 RangeInMeters;

	/* Socket where the projectile will come from */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meta, meta = (AllowPrivateAccess = "true"))
	FString ProjectileSocketName;

	/* The weapon's collision box */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meta, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WeaponCollision;

	/* Reference to the owning character's controller */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meta, meta = (AllowPrivateAccess = "true"))
	AActor* OwningActor;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetWeaponRangeInMeters() const;
	FString GetExpectedCharacterSocketNameForWeaponToBindTo() const;
	FORCEINLINE void SetOwningActor(AActor* Actor) { OwningActor = Actor; }

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	virtual void OnEndOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ActivateWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateWeapon();

	FVector GetProjectileSocketLocation();
	FRotator GetProjectileSocketForwardRotation();
};
