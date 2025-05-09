// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RswEnemyGameplayAbility.h"
#include "Characters/RswEnemyCharacter.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "RswGameplayTags.h"

ARswEnemyCharacter* URswEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!CachedRswEnemyCharacter.IsValid())
    {
        CachedRswEnemyCharacter = Cast<ARswEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }

    return CachedRswEnemyCharacter.IsValid() ? CachedRswEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* URswEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle URswEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetRswAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	// 这里source为什么也是Avatar
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetRswAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		RswGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	return EffectSpecHandle;
}
