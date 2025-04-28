// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"


class ARswWeaponBase;

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ARswWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    ARswWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

    UPROPERTY(BlueprintReadWrite, Category = "Rsw|Combat")
    FGameplayTag CurrentEquippedWeaponTag;

    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    ARswWeaponBase* GetCharacterCurrentEquippedWeapon() const;

private:
    TMap<FGameplayTag, ARswWeaponBase*> CharacterCarriedWeaponMap;
};
