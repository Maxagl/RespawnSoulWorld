// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RswHeroGameplayAbility.h"
#include "RswTypes/RswStructTypes.h"

#include "HeroGameplayAbility_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UHeroGameplayAbility_ChargeAttack : public URswHeroGameplayAbility
{
	GENERATED_BODY()
public:
    UHeroGameplayAbility_ChargeAttack();

    UPROPERTY(EditDefaultsOnly)
    FChargePhaseData ChargeConfig;
    FTimerHandle ChargeTimeHandle;
    UPROPERTY(BlueprintReadOnly)
    float ChargeTime = 0.0f;
    bool bIsCharging = false;
    UFUNCTION(BlueprintCallable)
    virtual void OnInputPressed();
    UFUNCTION(BlueprintCallable)
    virtual void OnInputReleased();
};
