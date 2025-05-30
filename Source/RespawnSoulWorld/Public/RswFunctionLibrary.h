// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RswTypes/RswEnumTypes.h"
#include "RswFunctionLibrary.generated.h"


class URswAbilitySystemComponent;
class UPawnCombatComponent;
struct FScalableFloat;
class URswGameInstance;

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
    static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

    static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
    static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ERswConfirmType& OutConfirmType);

    static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
    static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, ERswValidType& OutValidType);


    UFUNCTION(BlueprintPure, Category = "Rsw|FunctionLibrary")
    static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

    UFUNCTION(BlueprintPure, Category = "Rsw|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
    static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

    UFUNCTION(BlueprintPure, Category = "Rsw|FunctionLibrary")
    static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

    UFUNCTION(BlueprintPure, Category = "Rsw|FunctionLibrary")
    static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary")
    static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
    static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
        float& OutRemainingTime, ERswCountDownActionInput CountDownInput,
        UPARAM(DisplayName = "Output") ERswCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);

    UFUNCTION(BlueprintPure, Category = "Rsw|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
    static URswGameInstance* GetRswGameInstance(const UObject* WorldContextObject);


    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
    static void ToggleInputMode(const UObject* WorldContextObject, ERswInputMode InInputMode);


    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary")
    static void SaveCurrentGameDifficulty(ERswGameDifficulty InDifficultyToSave);

    UFUNCTION(BlueprintCallable, Category = "Rsw|FunctionLibrary")
    static bool TryLoadSavedGameDifficulty(ERswGameDifficulty& OutSavedDifficulty);
};
