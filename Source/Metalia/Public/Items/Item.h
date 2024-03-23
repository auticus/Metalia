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
	/* Skeletal Mesh for the Item - NOTE some items may need a static mesh instead */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Appearance, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* ItemMesh;

	/* The name of the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meta, meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FString GetItemName() const;
	USkeletalMeshComponent* GetItemMesh() const;

	void SetItemRenderCustomDepth(bool bValue) { ItemMesh->SetRenderCustomDepth(bValue); }
	void SetItemCustomDepthStencilValue(int Stencil) { ItemMesh->SetCustomDepthStencilValue(Stencil); }

	UFUNCTION(Client, Reliable)
	void Dissolve();

};
