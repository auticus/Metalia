// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MetaliaCharacterBase.generated.h"

UCLASS(Abstract)
class METALIA_API AMetaliaCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMetaliaCharacterBase();

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

public:

};
