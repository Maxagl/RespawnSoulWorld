// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_UpdateMaxWalkSpeed.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/RswEnemyCharacter.h"
#include "RswDebugHelper.h"
UBTTask_UpdateMaxWalkSpeed::UBTTask_UpdateMaxWalkSpeed()
{
    NodeName = TEXT("UpdateMaxWalkSpeed");
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_UpdateMaxWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    return EBTNodeResult::InProgress;
}

void UBTTask_UpdateMaxWalkSpeed::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    ARswEnemyCharacter* Owner = OwnerComp.GetAIOwner() ? Cast<ARswEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()) : nullptr;
    if (!Owner)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }
    float CurrentMaxWalkSpeed = Owner->GetCharacterMovement()->MaxWalkSpeed;
    Owner->GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(CurrentMaxWalkSpeed, Owner->ChasingMaxWalkSpeed, DeltaSeconds, 2);
    Owner->AddMovementInput(Owner->GetActorForwardVector(), Owner->GetCharacterMovement()->MaxWalkSpeed * DeltaSeconds);
    if (FMath::IsNearlyEqual(Owner->GetCharacterMovement()->MaxWalkSpeed, Owner->ChasingMaxWalkSpeed, 1.0f))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }
}
