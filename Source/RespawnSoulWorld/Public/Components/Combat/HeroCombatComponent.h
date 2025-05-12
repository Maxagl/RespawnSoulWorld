// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"


class ARswHeroWeapon;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    ARswHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    ARswHeroWeapon* GetHeroCurrentEquippedWeapon() const;

    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

    virtual void OnHitTargetActor(AActor* HitActor) override;
    virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
