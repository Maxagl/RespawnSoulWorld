// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitChargeRelease.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChargeRelease);

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UAbilityTask_WaitChargeRelease : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "Wait Charge Releas", HidePin = "OwningAbility", DefaultToSelf="OwningAbility"))
	static UAbilityTask_WaitChargeRelease* WaitChargeRelease(UGameplayAbility* OwningAbility, FGameplayTag GameplayTag);

	//~ Begin UGameplayTask Interface
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	//~ End UGameplayTask Interface

	/** 蓝图可绑定的回调 */
	UPROPERTY(BlueprintAssignable)
	FOnChargeRelease OnChargeReleased;

	void ChargeReleased(const FGameplayEventData* InPayload);
protected:
	bool bReleased = false;
	FGameplayTag CachedTag;


	FDelegateHandle DelegateHandle;
};
