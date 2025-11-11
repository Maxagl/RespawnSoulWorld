// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdatePatrolLocation.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UBTTask_UpdatePatrolLocation : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	void UpdatePatrolLocation(UBehaviorTreeComponent& OwnerComp);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PatrolKey;
};
