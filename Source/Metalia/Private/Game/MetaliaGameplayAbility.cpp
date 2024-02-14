// Copyright Auticus Studios


#include "Game/MetaliaGameplayAbility.h"
#include "GameplayTask.h"

void UMetaliaGameplayAbility::OnGameplayTaskActivated(UGameplayTask& Task)
{
	FString TaskName;
	Task.GetName(TaskName);

	FGameplayAbilityActorInfo OwningActor = GetActorInfo();
	auto Owner = OwningActor.OwnerActor;
	auto AvatarActor = OwningActor.AvatarActor;
	FString ActorName = Owner->GetActorNameOrLabel();
	FString AvatarName = AvatarActor->GetActorNameOrLabel();
}
