// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/RswGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(URswAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    check(InASCToGive);

    GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
    GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

    if (!StartUpGameplayEffects.IsEmpty())
    {
        for (const TSubclassOf < UGameplayEffect >& EffectClass : StartUpGameplayEffects)
        {
            if (!EffectClass) continue;

            UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
            // 谁拥有这个ASC，谁就拿这个效果，applytoself
            InASCToGive->ApplyGameplayEffectToSelf(
                EffectCDO,
                ApplyLevel,
                InASCToGive->MakeEffectContext()
            );
        }
    }

}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<URswGameplayAbility>>& InAbilitiesToGive, URswAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    if (InAbilitiesToGive.IsEmpty())
    {
        return;
    }

    for (const TSubclassOf<URswGameplayAbility>& Ability : InAbilitiesToGive)
    {
        if (!Ability) continue;

        FGameplayAbilitySpec AbilitySpec(Ability);
        AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;

        InASCToGive->GiveAbility(AbilitySpec);
    }
}
