// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"

/**
 * Inventory holding data pertaining to character inventory.
 */
UCLASS(Blueprintable, BlueprintType)
class METALIA_API UInventory : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMetaliaCharacterBase* CharacterReference;

	/* An array of the weapon classes that the character has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meta, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AWeapon>> AssignedWeaponClasses;

	/* Instantiated weapons that the pawn can equip */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meta, meta = (AllowPrivateAccess = "true"))
	TArray<AWeapon*> AvailableWeapons;

	/* The currently equipped weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meta, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

public:  //functions
	void InjectDependencies(class AMetaliaCharacterBase* CharacterReference);

	/* Goes through the AssignedWeaponClasses and creates instances of the weapons and puts them into AvailableWeapons */
	void SpawnAvailableWeapons();

	void AddWeaponSubclassToAvailableWeapons(TSubclassOf<AWeapon> WeaponTemplate);

	/* Assigns weapon element 0 to the character from AvailableWeapons*/
	void EquipDefaultWeapon();
	void EquipWeapon(AWeapon* Weapon); 
	void HandleWeaponsOnDeath();
	void DropEquippedWeaponsOnGround();

	UFUNCTION(BlueprintCallable)
	AWeapon* GetEquippedWeapon() const;

private:
	void FinishDropWeaponsOnGround() const;
};
