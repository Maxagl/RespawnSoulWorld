// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"
#include "Engine/AssetManager.h"
#include "NavigationSystem.h"
#include "Characters/RswEnemyCharacter.h"

#include "RswDebugHelper.h"

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<ARswEnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius)
{
    UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>(OwningAbility);
    Node->CachedEventTag = EventTag;
    Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
    Node->CachedNumToSpawn = NumToSpawn;
    Node->CachedSpawnOrigin = SpawnOrigin;
    Node->CachedRandomSpawnRadius = RandomSpawnRadius;

    return Node;
}

void UAbilityTask_WaitSpawnEnemies::Activate()
{
    Debug::Print(TEXT("Activate task, bind delegate"));
    FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

    DelegateHandle = Delegate.AddUObject(this, &ThisClass::OnGameplayEventReceived);
}

void UAbilityTask_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
    FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

    Delegate.Remove(DelegateHandle);

    Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
    // 这里相当于是我如果设置了需要spawn的类的话，我就进入资源加载环节
    // 没有设置的话就是broadcast didnotSpawn，结束task
    Debug::Print(TEXT("Received Event, spawn enemy"));
    if (ensure(!CachedSoftEnemyClassToSpawn.IsNull()))
    {
        UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
            CachedSoftEnemyClassToSpawn.ToSoftObjectPath(),
            FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded)
        );
    }
    else
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            DidNotSpawn.Broadcast(TArray<ARswEnemyCharacter*>());
        }

        EndTask();
    }
}

void UAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded()
{
    UClass* LoadedClass = CachedSoftEnemyClassToSpawn.Get();
    UWorld* World = GetWorld();

    // 这里也是保护机制，防止没法生成，却硬生成
    if (!LoadedClass || !World)
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            DidNotSpawn.Broadcast(TArray<ARswEnemyCharacter*>());
        }

        EndTask();

        return;
    }

    TArray<ARswEnemyCharacter*> SpawnedEnemies;

    FActorSpawnParameters SpawnParam;
    SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    for (int32 i = 0; i < CachedNumToSpawn; i++)
    {
        FVector RandomLocation;
        UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, CachedSpawnOrigin, RandomLocation, CachedRandomSpawnRadius);

        RandomLocation += FVector(0.f, 0.f, 50.f);

        const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

        ARswEnemyCharacter* SpawnedEnemy = World->SpawnActor<ARswEnemyCharacter>(LoadedClass, RandomLocation, SpawnFacingRotation, SpawnParam);

        if (SpawnedEnemy)
        {
            SpawnedEnemies.Add(SpawnedEnemy);
        }
    }

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        // 这次是生成完了，但是我继续保护防止没生成
        if (!SpawnedEnemies.IsEmpty())
        {
            OnSpawnFinished.Broadcast(SpawnedEnemies);
        }
        else
        {
            DidNotSpawn.Broadcast(TArray<ARswEnemyCharacter*>());
        }
    }
    EndTask();
}
