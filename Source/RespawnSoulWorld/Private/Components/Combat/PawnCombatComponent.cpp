// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/RswWeaponBase.h"
#include "Components/BoxComponent.h"

#include "RswDebugHelper.h"
void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ARswWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon, bool IsShield)
{

    checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
    check(InWeaponToRegister);

    CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
    if (bRegisterAsEquippedWeapon)
    {
        CurrentEquippedWeaponTag = InWeaponTagToRegister;
    }
    //if (!IsShield)
    //{
    //    checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
    //    check(InWeaponToRegister);

    //    CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
    //    if (bRegisterAsEquippedWeapon)
    //    {
    //        CurrentEquippedWeaponTag = InWeaponTagToRegister;
    //    }
    //}
    //else
    //{
    //    checkf(!CharacterCarriedShieldMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
    //    check(InWeaponToRegister);

    //    CharacterCarriedShieldMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
    //    CurrentEquippedShieldTag = InWeaponTagToRegister;
    //}
    InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
    InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);


    // const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s"), *InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
    // Debug::Print(WeaponString);
}

ARswWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
    if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
    {
        if (ARswWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
        {
            return *FoundWeapon;
        }
    }

    return nullptr;
}

ARswWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
    if (!CurrentEquippedWeaponTag.IsValid())
    {
        return nullptr;
    }

    return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}



void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
    if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
    {
        ToggleCurrentEquippedWeaponCollision(bShouldEnable);
    }
    else
    {
        //TODO:Handle body collision boxes
        ToggleBodyCollsionBoxCollision(bShouldEnable, ToggleDamageType);
    }
    
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{

}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{

}

void UPawnCombatComponent::ToggleCurrentEquippedWeaponCollision(bool bShouldEnable)
{
    ARswWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

    check(WeaponToToggle);

    if (bShouldEnable)
    {
        WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
    else
    {
        WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        OverlappedActors.Empty();
    }
}

void UPawnCombatComponent::ToggleBodyCollsionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
}
