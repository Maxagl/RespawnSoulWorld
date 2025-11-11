// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/RswStoneBase.h"
#include "Characters/RswHeroCharacter.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "RswGameplayTags.h"

void ARswStoneBase::Consume(URswAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnStoneConsumed();
}

void ARswStoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARswHeroCharacter* OverlappedHeroCharacter = Cast<ARswHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetRswAbilitySystemComponent()->TryActivateAbilityByTag(RswGameplayTags::Player_Ability_PickUp_Stones);
	}
}
