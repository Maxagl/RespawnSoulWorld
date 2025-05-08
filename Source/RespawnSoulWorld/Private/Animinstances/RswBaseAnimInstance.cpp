// Fill out your copyright notice in the Description page of Project Settings.


#include "Animinstances/RswBaseAnimInstance.h"
#include "RswFunctionLibrary.h"

bool URswBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return URswFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
