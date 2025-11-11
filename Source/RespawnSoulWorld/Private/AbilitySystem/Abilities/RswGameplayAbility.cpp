// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RswGameplayAbility.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "RswFunctionLibrary.h"
#include "RswGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

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

FActiveGameplayEffectHandle URswGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

    check(TargetASC && InSpecHandle.IsValid());

    return GetRswAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
        *InSpecHandle.Data,
        TargetASC
    );
}

FActiveGameplayEffectHandle URswGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ERswSuccessType& OutSuccessType)
{
    FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

    OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? ERswSuccessType::Successful : ERswSuccessType::Failed;

    return ActiveGameplayEffectHandle;
}

void URswGameplayAbility::ApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& InHitResults)
{
    if (InHitResults.IsEmpty())
    {
        return;
    }

    APawn* OwningPawn = CastChecked<APawn>(GetAvatarActorFromActorInfo());

    for (const FHitResult& Hit : InHitResults)
    {
        if (APawn* HitPawn = Cast<APawn>(Hit.GetActor()))
        {
            if (URswFunctionLibrary::IsTargetPawnHostile(OwningPawn, HitPawn))
            {
                FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(HitPawn, InSpecHandle);

                if (ActiveGameplayEffectHandle.WasSuccessfullyApplied())
                {
                    FGameplayEventData Data;
                    Data.Instigator = OwningPawn;
                    Data.Target = HitPawn;

                    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
                        HitPawn,
                        RswGameplayTags::Shared_Event_HitReact,
                        Data
                    );
                }
            }
        }
    }
}
