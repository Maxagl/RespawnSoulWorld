// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class URswGameUserSettings;

/**
 *
 */
class RESPAWNSOULWORLD_API FOptionsDataInteractionHelper
{
public:
	FOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath);

	FString GetValueAsString() const;
	void	SetValueFromString(const FString& InStringValue);

private:
	FCachedPropertyPath					 CachedDynamicFunctionPath;
	TWeakObjectPtr<URswGameUserSettings> CachedWeakGameUserSettings;
};
