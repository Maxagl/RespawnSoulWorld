// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitChargeRelease.h"
#include "AbilitySystemComponent.h"

UAbilityTask_WaitChargeRelease* UAbilityTask_WaitChargeRelease::WaitChargeRelease(UGameplayAbility* OwningAbility, FGameplayTag GameplayTag)
{
	UAbilityTask_WaitChargeRelease* Task = NewAbilityTask<UAbilityTask_WaitChargeRelease>(OwningAbility);
	Task->CachedTag = GameplayTag;
	return Task;
}

void UAbilityTask_WaitChargeRelease::Activate()
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedTag);
	DelegateHandle =  Delegate.AddUObject(this, &ThisClass::ChargeReleased);
}

void UAbilityTask_WaitChargeRelease::OnDestroy(bool bInOwnerFinished)
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedTag);

	Delegate.Remove(DelegateHandle);

	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_WaitChargeRelease::ChargeReleased(const FGameplayEventData* InPayload)
{
	OnChargeReleased.Broadcast();
}
