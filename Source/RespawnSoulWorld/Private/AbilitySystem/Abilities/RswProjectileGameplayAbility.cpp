// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RswProjectileGameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/RswEnemyCharacter.h"
#include "Characters/RswHeroCharacter.h"

void URswProjectileGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void URswProjectileGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

AActor* URswProjectileGameplayAbility::EnemyBoxTraceIgnoreEnemy()
{
	FVector start = GetEnemyCharacterFromActorInfo()->GetActorLocation();
	FVector end = start + GetEnemyCharacterFromActorInfo()->GetActorForwardVector() * 1000;

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetAvatarActorFromActorInfo(),
		start,
		end,
		TraceBoxSize / 2.f,
		GetEnemyCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		HitResults,
		true
	);
	for (auto HitResult : HitResults)
	{
		if (HitResult.GetActor()->GetClass()->IsChildOf(ARswHeroCharacter::StaticClass()))
		{
			return HitResult.GetActor();
		}
	}
	return nullptr;
}
