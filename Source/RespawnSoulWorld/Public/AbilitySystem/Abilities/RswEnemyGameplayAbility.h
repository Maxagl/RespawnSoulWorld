// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RswGameplayAbility.h"
#include "RswEnemyGameplayAbility.generated.h"

class ARswEnemyCharacter;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswEnemyGameplayAbility : public URswGameplayAbility
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "Rsw|Ability")
    ARswEnemyCharacter* GetEnemyCharacterFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Rsw|Ability")
    UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
    TWeakObjectPtr<ARswEnemyCharacter> CachedRswEnemyCharacter;
};
