// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HeroGameplayAbility_ChargeAttack.h"
#include "HeroGameplayAbility_RingOfGust.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMaxCharge);
class UGameplayCueManager;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UHeroGameplayAbility_RingOfGust : public UHeroGameplayAbility_ChargeAttack
{
	GENERATED_BODY()
public:
    virtual void OnInputPressed() override;
    virtual void OnInputReleased() override;
    void TickCharge();
    UPROPERTY(EditDefaultsOnly)
    FGameplayTag ReleaseTag;


protected:

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UGameplayEffect> GE_Cooldown_RingGust;
    UPROPERTY(EditDefaultsOnly)
    FGameplayTag CooldownTag;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag CooldownDurationTag;

    UFUNCTION(BlueprintCallable)
    bool CheckCoolDown() const;

    UFUNCTION(BlueprintCallable)
    void ApplyCoolDown(float CoolDownTime);

    UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
    void ExecuteChargedAttack(float NormalizedCharge);

    UPROPERTY(BlueprintAssignable)
    FOnMaxCharge OnMaxCharge;

    UPROPERTY(EditAnywhere, Category = Effects)
    class UNiagaraSystem* NiagaraSystem;

};
