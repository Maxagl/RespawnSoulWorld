// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "RswStructTypes.generated.h"

/**
 * 
 */
class URswHeroLinkedAnimLayer;
class UGameplayAbility;
class UInputMappingContext;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FChargePhaseData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta = (Categories = "ChargeData"))
    float MaxChargeTime;

    UPROPERTY(EditAnywhere, meta = (Categories = "ChargeData"))
    float Phase1Threshold;

    UPROPERTY(EditAnywhere, meta = (Categories = "ChargeData"))
    float Phase2Threshold;

    UPROPERTY(EditAnywhere, meta = (Categories = "ChargeData"))
    float CooldownLight;

    UPROPERTY(EditAnywhere, meta = (Categories = "ChargeData"))
    float CooldownHeavy;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UGameplayEffect> EffectToApply;

    // …其他如动画、VFX、音效、标签等
};

USTRUCT(BlueprintType)
struct FRswHeroAbilitySet
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
    FGameplayTag InputTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UGameplayAbility> AbilityToGrant;

    bool IsValid() const;
};


USTRUCT(BlueprintType)
struct FRswHeroSpecialAbilitySet : public FRswHeroAbilitySet
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSoftObjectPtr<UMaterialInterface> SoftAbilityIconMaterial;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Player.Cooldown"))
    FGameplayTag AbilityCooldownTag;
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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FRswHeroSpecialAbilitySet> SpecialWeaponAbilities;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FScalableFloat WeaponBaseDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};
