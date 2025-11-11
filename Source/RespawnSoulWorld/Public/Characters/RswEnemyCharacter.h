// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RswBaseCharacter.h"
#include "RswEnemyCharacter.generated.h"


class UEnemyCombatComponent;
class UEnemyUIComponent;
class UWidgetComponent;
class UBoxComponent;
class ATargetPoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossDead);
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API ARswEnemyCharacter : public ARswBaseCharacter
{
	GENERATED_BODY()
public:
    FOnBossDead OnBossDead;

    ARswEnemyCharacter();

    //~ Begin PawnCombatInterface Interface.
    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
    //~ End PawnCombatInterface Interface

    //~ Begin IPawnUIInterface Interface.
    virtual UPawnUIComponent* GetPawnUIComponent() const override;
    virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
    //~ End IPawnUIInterface Interface

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION()
    void HandleHeroEnterBossArea();
    UFUNCTION(BlueprintCallable)
    void BossDiedDestroyDoor();
    UFUNCTION()
    void ResetStatus();

    virtual void FakeDie() override;
    virtual void Respawn() override;

protected:
    virtual void BeginPlay() override;

    //~ Begin APawn Interface.
    virtual void PossessedBy(AController* NewController) override;
    //~ End APawn Interface

#if WITH_EDITOR
//~ Begin UObject Interface.
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
    //~ End UObject Interface
#endif

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Patrol")
    TArray<ATargetPoint*> PatrolLocations;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UEnemyCombatComponent* EnemyCombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UBoxComponent* LeftHandCollisionBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    FName LeftHandCollisionBoxAttachBoneName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UBoxComponent* RightHandCollisionBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    FName RightHandCollisionBoxAttachBoneName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UBoxComponent* LeftLegCollisionBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    FName LeftLegCollisionBoxAttachBoneName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UBoxComponent* RightLegCollisionBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    FName RightLegCollisionBoxAttachBoneName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UEnemyUIComponent* EnemyUIComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UWidgetComponent* EnemyHealthWidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    URswAbilitySystemComponent* RswAbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    URswAttributeSet* RswAttributeSet;

    UFUNCTION()
    virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    float ChasingMaxWalkSpeed = 200.f;
private:
    void InitEnemyStartUpData();

public:
    FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
    FORCEINLINE UBoxComponent* GetLeftHandCollisionBox() const { return LeftHandCollisionBox; }
    FORCEINLINE UBoxComponent* GetRightHandCollisionBox() const { return RightHandCollisionBox; }

    FORCEINLINE UBoxComponent* GetLeftLegCollisionBox() const { return LeftLegCollisionBox; }
    FORCEINLINE UBoxComponent* GetRightLegCollisionBox() const { return RightLegCollisionBox; }
    FORCEINLINE TArray<ATargetPoint*> GetPatrolLocations() const { return PatrolLocations; }

public:
    virtual URswAbilitySystemComponent* GetRswAbilitySystemComponent() const override;

    virtual URswAttributeSet* GetRswAttributeSet() const override;
};
