// Fill out your copyright notice in the Description page of Project Settings.


#include "Animinstances/Hero/RswHeroAnimInstance.h"
#include "Characters/RswHeroCharacter.h"

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
