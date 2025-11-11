// Fill out your copyright notice in the Description page of Project Settings.


#include "Animinstances/Hero/RswHeroAnimInstance.h"
#include "Characters/RswHeroCharacter.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "RswGameplayTags.h"

#include "RswDebugHelper.h"

void URswHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<ARswHeroCharacter>(OwningCharacter);
	}
}

void URswHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	URswAbilitySystemComponent* ASC = nullptr;

	if (OwningCharacter)
	{
		ASC = OwningHeroCharacter->GetRswAbilitySystemComponent();
	}

	if (ASC)
	{
		bShouldEnterRunningState = ASC->HasMatchingGameplayTag(RswGameplayTags::Player_Status_Running);
	}

	if (bHasAcceleration || (ASC && ASC->HasMatchingGameplayTag(RswGameplayTags::Player_Status_CombatMode)))
	{
		IdleElpasedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else if (!bHasAcceleration)
	{
		IdleElpasedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxtStateThreshold);
	}
}
