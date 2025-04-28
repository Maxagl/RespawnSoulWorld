// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/RswGameplayAbility.h"

void URswAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
    if (!InInputTag.IsValid())
    {
        return;
    }

    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

        TryActivateAbility(AbilitySpec.Handle);
    }
}

void URswAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

void URswAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FRswHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{

    if (InDefaultWeaponAbilities.IsEmpty())
    {
        return;
    }

    for (const FRswHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
    {
        if (!AbilitySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
        AbilitySpec.SourceObject = GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

        OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
    }
}

void URswAbilitySystemComponent::RemovedGrantedHeroWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
    if (InSpecHandlesToRemove.IsEmpty())
    {
        return;
    }

    for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
    {
        if (SpecHandle.IsValid())
        {
            ClearAbility(SpecHandle);
        }
    }

    InSpecHandlesToRemove.Empty();
}
