// Copyright Auticus Studios


#include "Game/AttributeInfo.h"

FMetaliaAttributeInfo UAttributeInfo::FindAttributeInfoFromTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FMetaliaAttributeInfo& Attribute : AttributeInformation)
	{
		if (Attribute.AttributeTag.MatchesTagExact(Tag))
		{
			return Attribute;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Tag passed in [%s] was not found in AttributeInfo Array"), *Tag.ToString());
	}

	return FMetaliaAttributeInfo();
}
