// Copyright Auticus Studios


#include "Items/Weapon.h"
#include "Components/BoxComponent.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystemComponent.h"
#include "Game/MetaliaDamageAbility.h"
#include "Engine/SkeletalMeshSocket.h"
#include "NiagaraComponent.h"
#include <NiagaraFunctionLibrary.h>

AWeapon::AWeapon() :
	bRequiresTwoHands(false),
	RangeInMeters(0)
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Hit Box"));
	WeaponCollision->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	// make sure weapon is ignoring everything, turn it on as needed
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	WeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	// called when an instance of the class is placed in editor or spawned
	Super::OnConstruction(Transform);

	// this was used to populate the item from a WeaponDataTable (refer to Killmeister)
	// as no weapon data table is being used, this will currently do nothing but is a placeholder
	// for educational purpose.
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 AWeapon::GetWeaponRangeInMeters() const
{
	return RangeInMeters;
}

FString AWeapon::GetExpectedCharacterSocketNameForWeaponToBindTo() const
{
	return SocketName;
}

void AWeapon::ActivateWeapon()
{
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ActorsHitByWeapon.Empty(); // prepare the array for a new set of actors we hit
}

void AWeapon::DeactivateWeapon()
{
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

FVector AWeapon::GetProjectileSocketLocation()
{
	if (ProjectileSocketName == "") return FVector();
	
	return GetItemMesh()->GetSocketLocation(FName(ProjectileSocketName));
}

FVector AWeapon::GetImpactSocketLocation()
{
	if (ImpactSocketName == "") return FVector();
	return GetItemMesh()->GetSocketLocation(FName(ImpactSocketName));
}

FRotator AWeapon::GetProjectileSocketForwardRotation()
{
	if (ProjectileSocketName == "") return FRotator();

	return GetItemMesh()->GetForwardVector().Rotation();
}

USoundBase* AWeapon::GetImpactSound()
{
	return ImpactSound;
}

void AWeapon::GenerateWeaponPreShotAura()
{
	if (PreShotAuraSocketName == "" || Vfx_PreShotAura == nullptr || ItemMesh == nullptr) return;
	
	const USkeletalMeshSocket* WeaponAuraFxSocket = ItemMesh->GetSocketByName(FName(PreShotAuraSocketName));
	if (WeaponAuraFxSocket == nullptr) return;

	const FVector WeaponAuraFxTransform = WeaponAuraFxSocket->GetSocketTransform(ItemMesh).GetLocation();
	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Vfx_PreShotAura, WeaponAuraFxTransform);
}

void AWeapon::OnOverlap(AActor* TargetActor)
{
	// this should be activated and deactivated via the anim blueprints and anim montages that will call Activate or Deactivate
	// this should also be primarily if not solely dealing with melee weapons.
	if (TargetActor == OwningActor) return;  //if I am hitting myself don't register this

	// DEBUG Info
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Weapon has hit %s"), *TargetActor->GetName()));

	/* In keeping consistency with the projectile it is up to the blueprint to define the overlap function and call this */
	if (HasAuthority())
	{
		ICombatInterface* CI = Cast<ICombatInterface>(OwningActor);
		checkf(CI, TEXT("Weapon is owned by an actor that does not implement the proper combat interface"));

		// HasAuthority() is a bit of a liar.  It doesn't mean on the server.  A client spawns a character, like a player on a client-side
		// and that character is now owned and has authority by their machine.
		if (!ActorsHitByWeapon.Contains(TargetActor))
		{
			ActorsHitByWeapon.Add(TargetActor);
			CI->CauseDamageToTarget_Implementation(TargetActor);
		}
	}
}

void AWeapon::OnEndOverlap(AActor* TargetActor)
{
}
