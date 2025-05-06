// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RswBaseCharacter.h"
#include "RswEnemyCharacter.generated.h"


class UEnemyCombatComponent;
class UEnemyUIComponent;
class UWidgetComponent;
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

    //~ Begin IPawnUIInterface Interface.
    virtual UPawnUIComponent* GetPawnUIComponent() const override;
    virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
    //~ End IPawnUIInterface Interface

protected:
    virtual void BeginPlay() override;

    //~ Begin APawn Interface.
    virtual void PossessedBy(AController* NewController) override;
    //~ End APawn Interface
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UEnemyCombatComponent* EnemyCombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UEnemyUIComponent* EnemyUIComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UWidgetComponent* EnemyHealthWidgetComponent;


private:
    void InitEnemyStartUpData();

public:
    FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
