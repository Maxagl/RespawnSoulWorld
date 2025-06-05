// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_UpdatePatrolLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Characters/RswEnemyCharacter.h"
#include "Engine/TargetPoint.h"

#include "RswDebugHelper.h"

void UBTTask_UpdatePatrolLocation::UpdatePatrolLocation(UBehaviorTreeComponent& OwnerComp)
{
	if (ARswEnemyCharacter* EnemyOwnThisBT = Cast<ARswEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		TArray<ATargetPoint*> Patrols = EnemyOwnThisBT->GetPatrolLocations();
		if (Patrols.Num() == 0)
		{
			return;
		}
		int32 RandomIndex = FMath::RandRange(0, Patrols.Num() - 1);
		
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(PatrolKey.SelectedKeyName, Patrols[RandomIndex]);
	}
}

EBTNodeResult::Type UBTTask_UpdatePatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetBlackboardComponent())
	{
		UpdatePatrolLocation(OwnerComp);
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Succeeded;
}
