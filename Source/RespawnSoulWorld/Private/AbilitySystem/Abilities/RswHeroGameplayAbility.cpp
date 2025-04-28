// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RswHeroGameplayAbility.h"
#include "Characters/RswHeroCharacter.h"
#include "Controllers/RswHeroController.h"

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