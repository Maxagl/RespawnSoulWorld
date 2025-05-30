// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RswEnemyGameplayAbility.h"
#include "RswProjectileGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswProjectileGameplayAbility : public URswEnemyGameplayAbility
{
	GENERATED_BODY()
protected:
	//~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface	
public:
	UFUNCTION(BlueprintCallable)
	AActor* EnemyBoxTraceIgnoreEnemy();

	UPROPERTY(EditDefaultsOnly, Category = "TracePlayer")
	float BoxTraceDistance = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "TracePlayer")
	FVector TraceBoxSize = FVector(1000.f, 1000.f, 300.f);

	UPROPERTY(EditDefaultsOnly, Category = "TracePlayer")
	TArray< TEnumAsByte < EObjectTypeQuery > > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	bool bShowPersistentDebugShape = false;
};
