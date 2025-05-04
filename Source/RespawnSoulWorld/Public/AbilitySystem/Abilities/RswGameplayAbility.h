// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RswTypes/RswEnumTypes.h"
#include "RswGameplayAbility.generated.h"

class UPawnCombatComponent;
class URswAbilitySystemComponent;

UENUM(BlueprintType)
enum class ERswAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
    //~ Begin UGameplayAbility Interface.
    virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
    //~ End UGameplayAbility Interface

    UPROPERTY(EditDefaultsOnly, Category = "RswAbility")
    ERswAbilityActivationPolicy AbilityActivationPolicy = ERswAbilityActivationPolicy::OnTriggered;

    UFUNCTION(BlueprintPure, Category = "Rsw|Ability")
    UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

    UFUNCTION(BlueprintPure, Category = "Rsw|Ability")
    URswAbilitySystemComponent* GetRswAbilitySystemComponentFromActorInfo() const;

    FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

    UFUNCTION(BlueprintCallable, Category = "Rsw|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
    FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ERswSuccessType& OutSuccessType);

};
