// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RswGameplayAbility.h"
#include "RswHeroGameplayAbility.generated.h"

class ARswHeroCharacter;
class ARswHeroController;
class UHeroCombatComponent;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswHeroGameplayAbility : public URswGameplayAbility
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintPure, Category = "Rsw|Ability")
    ARswHeroCharacter* GetHeroCharacterFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Rsw|Ability")
    ARswHeroController* GetHeroControllerFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Rsw|Ability")
    UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Rsw|Ability")
    FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

    UFUNCTION(BlueprintCallable, Category = "Rsw|Ability")
    bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);

private:
    TWeakObjectPtr<ARswHeroCharacter> CachedRswHeroCharacter;
    TWeakObjectPtr<ARswHeroController> CachedRswHeroController;
};
