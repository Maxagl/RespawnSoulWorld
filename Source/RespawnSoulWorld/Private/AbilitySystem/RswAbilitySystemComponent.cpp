// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/RswHeroGameplayAbility.h"
#include "RswGameplayTags.h"

void URswAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
    if (!InInputTag.IsValid())
    {
        return;
    }

    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

        if (InInputTag.MatchesTag(RswGameplayTags::InputTag_Toggleable))
        {
            if (AbilitySpec.IsActive())
            {
                CancelAbilityHandle(AbilitySpec.Handle);
            }
            else
            {
                TryActivateAbility(AbilitySpec.Handle);
            }
        }
        else
        {
            TryActivateAbility(AbilitySpec.Handle);
        }
    }
}

void URswAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
    if (!InInputTag.IsValid() || !InInputTag.MatchesTag(RswGameplayTags::InputTag_MustBeHeld))
    {
        return;
    }

    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
        {
            CancelAbilityHandle(AbilitySpec.Handle);
        }
    }
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

bool URswAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
    check(AbilityTagToActivate.IsValid());

    TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
    GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

    if (!FoundAbilitySpecs.IsEmpty())
    {
        const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
        FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

        check(SpecToActivate);

        if (!SpecToActivate->IsActive())
        {
            return TryActivateAbility(SpecToActivate->Handle);
        }
    }
    return false;
}
