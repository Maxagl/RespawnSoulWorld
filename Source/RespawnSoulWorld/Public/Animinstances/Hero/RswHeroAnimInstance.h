// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animinstances/RswCharacterAnimInstance.h"
#include "RswHeroAnimInstance.generated.h"

class ARswHeroCharacter;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswHeroAnimInstance : public URswCharacterAnimInstance
{
	GENERATED_BODY()
public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
    ARswHeroCharacter* OwningHeroCharacter;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
    bool bShouldEnterRelaxState;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
    float EnterRelaxtStateThreshold = 5.f;

    float IdleElpasedTime;
};
