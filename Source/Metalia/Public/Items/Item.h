// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class METALIA_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	/* Skeletal Mesh for the Item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Appearance, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* ItemMesh;

	/* The name of the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meta, meta = (AllowPrivateAccess = "true"))
	FString ItemName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FString GetItemName() const;
	USkeletalMeshComponent* GetItemMesh() const;

};
