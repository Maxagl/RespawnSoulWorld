// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RswEnemyGameplayAbility.h"
#include "Characters/RswEnemyCharacter.h"

ARswEnemyCharacter* URswEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!CachedRswEnemyCharacter.IsValid())
    {
        CachedRswEnemyCharacter = Cast<ARswEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }

    return CachedRswEnemyCharacter.IsValid() ? CachedRswEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* URswEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
