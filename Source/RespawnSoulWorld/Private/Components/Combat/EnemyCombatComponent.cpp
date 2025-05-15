// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "RswGameplayTags.h"
#include "RswFunctionLibrary.h"
#include "Characters/RswEnemyCharacter.h"
#include "Components/BoxComponent.h"


#include "RswDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	//TODO:: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = URswFunctionLibrary::NativeDoesActorHaveTag(HitActor, RswGameplayTags::Player_Status_Blocking);;
	const bool bIsMyAttackUnblockable = URswFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), RswGameplayTags::Enemy_Status_Unbloackable);;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		//TODO::check if the block is valid
		bIsValidBlock = URswFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			RswGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			RswGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}

}

void UEnemyCombatComponent::ToggleBodyCollsionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	ARswEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<ARswEnemyCharacter>();

	check(OwningEnemyCharacter);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();
	UBoxComponent* LeftLegCollisionBox = OwningEnemyCharacter->GetLeftLegCollisionBox();
	UBoxComponent* RightLegCollisionBox = OwningEnemyCharacter->GetRightLegCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox && LeftLegCollisionBox && RightLegCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::LeftLeg:
		LeftLegCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	case EToggleDamageType::RightLeg:
		RightLegCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
