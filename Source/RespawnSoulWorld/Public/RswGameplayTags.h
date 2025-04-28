// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"

namespace RwsGameplayTags
{
    /** Input Tags **/
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipSword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipSword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Sword);

    /** Player tags **/
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);


    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);
}