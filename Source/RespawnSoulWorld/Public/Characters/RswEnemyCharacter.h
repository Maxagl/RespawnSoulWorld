// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RswBaseCharacter.h"
#include "RswEnemyCharacter.generated.h"


class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API ARswEnemyCharacter : public ARswBaseCharacter
{
	GENERATED_BODY()
public:
    ARswEnemyCharacter();

    //~ Begin PawnCombatInterface Interface.
    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
    //~ End PawnCombatInterface Interface

protected:
    //~ Begin APawn Interface.
    virtual void PossessedBy(AController* NewController) override;
    //~ End APawn Interface
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UEnemyCombatComponent* EnemyCombatComponent;


private:
    void InitEnemyStartUpData();

public:
    FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
