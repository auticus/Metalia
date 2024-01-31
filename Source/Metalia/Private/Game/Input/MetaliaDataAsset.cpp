// Copyright Auticus Studios


#include "Game/Input/MetaliaDataAsset.h"
#include "InputAction.h"

const UInputAction* UMetaliaDataAsset::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FMetaliaInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("MyDataAssetAbilityInputAction %s could not be found on InputConfig."), *InputTag.ToString());
	return nullptr;
}
