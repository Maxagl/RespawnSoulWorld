// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/RswEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(URswAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

    if (!EnemyCombatAbilities.IsEmpty())
    {
        for (const TSubclassOf < URswEnemyGameplayAbility >& AbilityClass : EnemyCombatAbilities)
        {
            if (!AbilityClass) continue;

            FGameplayAbilitySpec AbilitySpec(AbilityClass);
            AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
            AbilitySpec.Level = ApplyLevel;

            InASCToGive->GiveAbility(AbilitySpec);
        }
    }
}
