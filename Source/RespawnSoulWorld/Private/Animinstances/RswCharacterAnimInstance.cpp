// Fill out your copyright notice in the Description page of Project Settings.


#include "Animinstances/RswCharacterAnimInstance.h"
#include "Characters/RswBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void URswCharacterAnimInstance::NativeInitializeAnimation()
{
    OwningCharacter = Cast<ARswBaseCharacter>(TryGetPawnOwner());

    if (OwningCharacter)
    {
        OwningMovementComponent = OwningCharacter->GetCharacterMovement();
    }
}

void URswCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    if (!OwningCharacter || !OwningMovementComponent)
    {
        return;
    }

    GroundSpeed = OwningCharacter->GetVelocity().Size2D();

    bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
