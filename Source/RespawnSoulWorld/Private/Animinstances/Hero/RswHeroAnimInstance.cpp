// Fill out your copyright notice in the Description page of Project Settings.


#include "Animinstances/Hero/RswHeroAnimInstance.h"
#include "Characters/RswHeroCharacter.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "RswGameplayTags.h"

#include "RswDebugHelper.h"

void URswHeroAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (OwningCharacter)
    {
        OwningHeroCharacter = Cast<ARswHeroCharacter>(OwningCharacter);
    }
}

void URswHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
    if (OwningHeroCharacter)
    {
        bShouldEnterRunningState = OwningHeroCharacter->GetRswAbilitySystemComponent()->HasMatchingGameplayTag(RswGameplayTags::Player_Status_Running);
    }
    
    if (bHasAcceleration)
    {
        IdleElpasedTime = 0.f;
        bShouldEnterRelaxState = false;
    }
    else
    {
        IdleElpasedTime += DeltaSeconds;
        bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxtStateThreshold);
    }
}
