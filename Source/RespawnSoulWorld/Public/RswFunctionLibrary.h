// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RswFunctionLibrary.generated.h"


class URswAbilitySystemComponent;
UENUM()
enum class ERswConfirmType : uint8
{
    Yes,
    No
};
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
    static URswAbilitySystemComponent* NativeGetRswASCFromActor(AActor* InActor);

    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary")
    static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary")
    static void RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

    static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
    static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ERswConfirmType& OutConfirmType);
};
