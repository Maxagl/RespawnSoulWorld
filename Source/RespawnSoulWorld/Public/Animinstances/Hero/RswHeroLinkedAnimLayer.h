// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animinstances/RswBaseAnimInstance.h"
#include "RswHeroLinkedAnimLayer.generated.h"

class URswHeroAnimInstance;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswHeroLinkedAnimLayer : public URswBaseAnimInstance
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    URswHeroAnimInstance* GetHeroAnimInstance() const;
};
