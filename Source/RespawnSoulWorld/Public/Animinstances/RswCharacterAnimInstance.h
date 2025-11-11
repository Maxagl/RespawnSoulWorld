// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animinstances/RswBaseAnimInstance.h"
#include "RswCharacterAnimInstance.generated.h"

class ARswBaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswCharacterAnimInstance : public URswBaseAnimInstance
{
	GENERATED_BODY()
public:
    virtual void NativeInitializeAnimation() override;
    // ¿‡À∆tick
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

protected:
    UPROPERTY()
    ARswBaseCharacter* OwningCharacter;

    UPROPERTY()
    UCharacterMovementComponent* OwningMovementComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
    float GroundSpeed;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
    bool bHasAcceleration;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
    float LocomotionDirection;
};
