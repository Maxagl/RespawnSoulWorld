// Fill out your copyright notice in the Description page of Project Settings.


#include "RswFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"

URswAbilitySystemComponent* URswFunctionLibrary::NativeGetRswASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<URswAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void URswFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	URswAbilitySystemComponent* ASC = NativeGetRswASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void URswFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	URswAbilitySystemComponent* ASC = NativeGetRswASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool URswFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	URswAbilitySystemComponent* ASC = NativeGetRswASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void URswFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ERswConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ERswConfirmType::Yes : ERswConfirmType::No;
}

UPawnCombatComponent* URswFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* URswFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, ERswValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? ERswValidType::Valid : ERswValidType::Invalid;

	return CombatComponent;
}
