// Copyright Auticus Studios


#include "AI/BPService_FindPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"


void UBPService_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwningPawn = AIOwner->GetPawn();

	// if actor is a player (like a pet or something) then look for enemy, otherwise find a Player
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag);

	// this in particular right now is going to find nearest instead of the most dangerous (heat)
}
