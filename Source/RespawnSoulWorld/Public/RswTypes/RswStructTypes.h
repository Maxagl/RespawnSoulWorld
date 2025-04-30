// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "RswStructTypes.generated.h"

/**
 * 
 */
class URswHeroLinkedAnimLayer;
class URswHeroGameplayAbility;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FRswHeroAbilitySet
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
    FGameplayTag InputTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<URswHeroGameplayAbility> AbilityToGrant;

    bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FRswHeroWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<URswHeroLinkedAnimLayer> WeaponAnimLayerToLink;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputMappingContext* WeaponInputMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FRswHeroAbilitySet> DefaultWeaponAbilities;
};
