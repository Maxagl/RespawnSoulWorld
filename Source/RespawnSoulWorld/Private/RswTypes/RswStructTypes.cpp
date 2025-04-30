// Fill out your copyright notice in the Description page of Project Settings.


#include "RswTypes/RswStructTypes.h"

#include "AbilitySystem/Abilities/RswHeroGameplayAbility.h"

bool FRswHeroAbilitySet::IsValid() const
{
    return InputTag.IsValid() && AbilityToGrant;
}
