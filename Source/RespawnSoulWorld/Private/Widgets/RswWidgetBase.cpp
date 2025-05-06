// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/RswWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

#include "RswDebugHelper.h"

void URswWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    // Debug::Print(TEXT("IN Initialized"));
    if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
    {
        if (UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
        {
            BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
        }
    }
}

void URswWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
    if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
    {
        UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

        checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

        BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
    }
}
