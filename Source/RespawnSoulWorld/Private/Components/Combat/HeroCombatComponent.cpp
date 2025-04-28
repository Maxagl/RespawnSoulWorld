// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/RswHeroWeapon.h"

ARswHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<ARswHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
