// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "GameplayTagContainer.h"
#include "HeroUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityIconSlotUpdatedDelegate, FGameplayTag, AbilityInputTag, TSoftObjectPtr<UMaterialInterface>, SoftAbilityIconMaterial);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilityCooldownBeginDelegate, FGameplayTag, AbilityInputTag, float, TotalCooldownTime, float, RemainingCooldownTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancleAbilityCooldownBeginDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoneInteractedDelegate, bool, bShouldDisplayInputKey);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorInteractedDelegate, bool, bShouldDisplayEnterDoorKey);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayChargeBar, bool, bShouldDisplayChargeBar);

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnPercentChangedDelegate OnCurrentRageChanged;

    UPROPERTY(BlueprintAssignable)
    FOnPercentChangedDelegate OnChargeTimeChanged;

    UPROPERTY(BlueprintAssignable)
    FOnDisplayChargeBar OnDisplayChargeBar;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnAbilityIconSlotUpdatedDelegate OnAbilityIconSlotUpdated;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnCancleAbilityCooldownBeginDelegate OnCancleAbilityCooldownBegin;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnAbilityCooldownBeginDelegate OnAbilityCooldownBegin;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnStoneInteractedDelegate OnStoneInteracted;

    // 控制交互按键的显示
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnDoorInteractedDelegate OnDoorInteracted;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnDoorInteractedDelegate OnCampfireInteracted;
};
