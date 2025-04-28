// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RswGameplayAbility.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void URswGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec); 

    if (AbilityActivationPolicy == ERswAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo && !Spec.IsActive())
        {
            ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
        }
    }
}

void URswGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    if (AbilityActivationPolicy == ERswAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo)
        {
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }
}

UPawnCombatComponent* URswGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

URswAbilitySystemComponent* URswGameplayAbility::GetRswAbilitySystemComponentFromActorInfo() const
{
    return Cast<URswAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
