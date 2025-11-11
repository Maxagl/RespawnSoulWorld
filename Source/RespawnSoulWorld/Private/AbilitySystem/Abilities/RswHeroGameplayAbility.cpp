// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RswHeroGameplayAbility.h"
#include "Characters/RswHeroCharacter.h"
#include "Controllers/RswHeroController.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "RswGameplayTags.h"


ARswHeroCharacter* URswHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedRswHeroCharacter.IsValid())
    {
        CachedRswHeroCharacter = Cast<ARswHeroCharacter>(CurrentActorInfo->AvatarActor);
    }

    return CachedRswHeroCharacter.IsValid() ? CachedRswHeroCharacter.Get() : nullptr;
}

ARswHeroController* URswHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedRswHeroController.IsValid())
    {
        CachedRswHeroController = Cast<ARswHeroController>(CurrentActorInfo->PlayerController);
    }

    return CachedRswHeroController.IsValid() ? CachedRswHeroController.Get() : nullptr;
}

UHeroCombatComponent* URswHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

UHeroUIComponent* URswHeroGameplayAbility::GetHeroUIComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroUIComponent();
}

FGameplayEffectSpecHandle URswHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
    check(EffectClass);

    FGameplayEffectContextHandle ContextHandle = GetRswAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle EffectSpecHandle = GetRswAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );

    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        RswGameplayTags::Shared_SetByCaller_BaseDamage,
        InWeaponBaseDamage
    );

    if (InCurrentAttackTypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
    }

    return EffectSpecHandle;
}

FGameplayEffectSpecHandle URswHeroGameplayAbility::MakeHeroMagicDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, float BufferMagnitued)
{
    check(EffectClass);
    FGameplayEffectContextHandle ContexHandle = GetRswAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContexHandle.SetAbility(this);
    ContexHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContexHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle EffectSpecHandle = GetRswAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(),
        ContexHandle
    );
    EffectSpecHandle.Data->SetSetByCallerMagnitude(RswGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);
    if (InCurrentAttackTypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(RswGameplayTags::Player_SetByCaller_AttackType_Magic_Wind, 1);
    }
    if (GetRswAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(RswGameplayTags::Shared_SetByCaller_Buff_WindMastery))
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(RswGameplayTags::Shared_SetByCaller_Buff_WindMastery, BufferMagnitued);
    }
    return EffectSpecHandle;
}

bool URswHeroGameplayAbility::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime)
{
    check(InCooldownTag.IsValid());

    FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

    TArray< TPair <float, float> > TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

    if (!TimeRemainingAndDuration.IsEmpty())
    {
        RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
        TotalCooldownTime = TimeRemainingAndDuration[0].Value;
    }

    return RemainingCooldownTime > 0.f;
}
