// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"


class ARswWeaponBase;


UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
    CurrentEquippedWeapon,
    LeftHand,
    RightHand
};
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
    // Weapon
    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ARswWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false, bool IsShield = false);

    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    ARswWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

    UPROPERTY(BlueprintReadWrite, Category = "Rsw|Combat")
    FGameplayTag CurrentEquippedWeaponTag;

    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    ARswWeaponBase* GetCharacterCurrentEquippedWeapon() const;

    // Shield
    UPROPERTY(BlueprintReadWrite, Category = "Rsw|Combat")
    FGameplayTag CurrentEquippedShieldTag;


    UFUNCTION(BlueprintCallable, Category = "Rsw|Combat")
    void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

    virtual void OnHitTargetActor(AActor* HitActor);
    virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
    TArray<AActor*> OverlappedActors;

private:
    TMap<FGameplayTag, ARswWeaponBase*> CharacterCarriedWeaponMap;
    TMap<FGameplayTag, ARswWeaponBase*> CharacterCarriedShieldMap;
};
