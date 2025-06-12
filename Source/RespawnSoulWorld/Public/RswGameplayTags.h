// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"

namespace RswGameplayTags
{
    /** Input Tags **/
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
  
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipSword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipSword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Sword);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipShield);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipShield);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Shield);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Shield);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Roll);
    
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SwitchTarget);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Light);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Heavy);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_PickUp_Stones);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EnterDoor);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Run);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_Rage);

    /** Player tags **/
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Shield);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Shield);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Shield);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Run);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetLock);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Rage);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Light);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Heavy);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_PickUp_Stones);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Light);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Heavy);


    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Shield);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Shield);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Shield);


    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SuccessfulBlock);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Left);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Right);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ActivateRage);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_AOE);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ConsumeStones);
    //UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_EnterDoor);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rolling);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Running);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Blocking);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_TargetLock);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Activating);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Active);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Full);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_None);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

    /** Enemy tags **/
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SummonEnemies);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SpawnStone);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);


    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Unbloackable);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_SummonEnemies);

    /** Shared tags **/
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile);
    

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Invincible);

    /** Game Data tags **/
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_SurvivalGameModeMap);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_MainMenuMap);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_SaveGame_Slot_1);
}