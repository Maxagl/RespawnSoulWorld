// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RswBaseCharacter.h"
#include "RswPlayerState.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "AbilitySystem/RswAttributeSet.h"
#include "MotionWarpingComponent.h"
// Sets default values
ARswBaseCharacter::ARswBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;

    GetMesh()->bReceivesDecals = false;
    MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* ARswBaseCharacter::GetAbilitySystemComponent() const
{
    return nullptr;
}

UPawnCombatComponent* ARswBaseCharacter::GetPawnCombatComponent() const
{
    return nullptr;
}

UPawnUIComponent* ARswBaseCharacter::GetPawnUIComponent() const
{
    return nullptr;
}

void ARswBaseCharacter::FakeDie()
{
}

void ARswBaseCharacter::Respawn()
{
}

void ARswBaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
}

URswAbilitySystemComponent* ARswBaseCharacter::GetRswAbilitySystemComponent() const
{
    return nullptr;
}

URswAttributeSet* ARswBaseCharacter::GetRswAttributeSet() const
{
    return nullptr;
}

