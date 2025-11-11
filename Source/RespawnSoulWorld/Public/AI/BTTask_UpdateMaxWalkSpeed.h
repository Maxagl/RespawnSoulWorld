// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateMaxWalkSpeed.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UBTTask_UpdateMaxWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_UpdateMaxWalkSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
