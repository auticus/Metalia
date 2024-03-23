// Copyright Auticus Studios


#include "Items/Inventory.h"
#include "Characters/MetaliaCharacterBase.h"
#include "Items/Weapon.h"
#include "Engine/SkeletalMeshSocket.h"

void UInventory::InjectDependencies(AMetaliaCharacterBase* Character)
{
	CharacterReference = Character;
}

void UInventory::AddWeaponSubclassToAvailableWeapons(TSubclassOf<AWeapon> WeaponTemplate)
{
	AssignedWeaponClasses.Add(WeaponTemplate);
}

void UInventory::SpawnAvailableWeapons()
{
	for (TSubclassOf<AWeapon> WeaponTemplate : AssignedWeaponClasses)
	{
		AWeapon* Weapon = CharacterReference->GetWorld()->SpawnActor<AWeapon>(WeaponTemplate);
		Weapon->SetOwningActor(CharacterReference);
		AvailableWeapons.Add(Weapon);
	}
}

void UInventory::EquipDefaultWeapon()
{
	if (AvailableWeapons.Num() == 0) return;

	if (AvailableWeapons.Num() == 1 && AvailableWeapons[0] == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Check your available weapons in blueprint, one is said to exist but is null"));
		return;
	}

	EquipWeapon(AvailableWeapons[0]);
}

void UInventory::EquipWeapon(AWeapon* Weapon)
{
	// TODO: will need to change animation blendspaces per weapon, right now its just hardcoded to use whatever we've given it
	checkf(Weapon, TEXT("Inventory::EquipWeapon was sent a weapon that is null"));

	if (Weapon)
	{
		// find the socket we are binding this weapon to on the character
		if (const USkeletalMeshSocket* WeaponSocket = CharacterReference->GetMesh()->GetSocketByName(FName(*Weapon->GetExpectedCharacterSocketNameForWeaponToBindTo())))
		{
			const FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, true);
			Weapon->GetItemMesh()->DetachFromComponent(Rules);

			if (WeaponSocket->AttachActor(Weapon, CharacterReference->GetMesh()) == false)
			{
				UE_LOG(LogTemp, Error, TEXT("Was unable to successfully attach weapon to character socket"));
			}
		}
		else
		{
			auto CharacterSocketName = Weapon->GetExpectedCharacterSocketNameForWeaponToBindTo();
			UE_LOG(LogTemp, Error, TEXT("Failed to attach weapon to socket '%s', check to make sure this socket exists or the blueprint has the correct socket"), *CharacterSocketName);
		}
	}

	EquippedWeapon = Weapon;
}

void UInventory::HandleWeaponsOnDeath()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->DeactivateWeapon();
	}
}

void UInventory::DropEquippedWeaponsOnGround()
{
	const FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, true);
	if (EquippedWeapon)
	{
		EquippedWeapon->DeactivateWeapon();
		EquippedWeapon->GetItemMesh()->DetachFromComponent(Rules);
		if (auto WeaponRoot = Cast<UPrimitiveComponent>(EquippedWeapon->GetRootComponent()))
		{
			WeaponRoot->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			WeaponRoot->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

			WeaponRoot->SetSimulatePhysics(true);
			WeaponRoot->SetEnableGravity(true);

			FTimerHandle DeathTimerHandle;
			CharacterReference->GetWorldTimerManager().SetTimer(
				DeathTimerHandle,
				this,
				&UInventory::FinishDropWeaponsOnGround,
				3.f);
		}
	}
}

void UInventory::FinishDropWeaponsOnGround() const
{
	// once we are no longer simulating physics, that means weapon is on the ground - turn timer off and disable all of the physics
	const auto WeaponRoot = Cast<UPrimitiveComponent>(EquippedWeapon->GetRootComponent());
	if (WeaponRoot)
	{
		WeaponRoot->SetSimulatePhysics(false);
		WeaponRoot->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponRoot->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		WeaponRoot->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	}
}

AWeapon* UInventory::GetEquippedWeapon() const
{
	return EquippedWeapon;
}