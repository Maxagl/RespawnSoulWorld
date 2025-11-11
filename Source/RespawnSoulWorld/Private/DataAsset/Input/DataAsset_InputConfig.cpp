// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FRswInputActionConfig& NativeInputAction : NativeInputActions)
	{
		if (NativeInputAction.InputTag == InInputTag)
		{
			return NativeInputAction.InputAction;
		}
	}
	return nullptr;
}
