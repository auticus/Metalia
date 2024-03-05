// Copyright Auticus Studios

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MetaliaAIController.generated.h"

class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class METALIA_API AMetaliaAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMetaliaAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
