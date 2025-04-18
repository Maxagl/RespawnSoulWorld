// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RswBaseCharacter.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "AbilitySystem/RswAttributeSet.h"

// Sets default values
ARswBaseCharacter::ARswBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


    PrimaryActorTick.bStartWithTickEnabled = false;

    GetMesh()->bReceivesDecals = false;

    RswAbilitySystemComponent = CreateDefaultSubobject<URswAbilitySystemComponent>(TEXT("RswAbilitySystemComponent"));
    RswAttributeSet = CreateDefaultSubobject<URswAttributeSet>(TEXT("RswAttributeSet"));

}

UAbilitySystemComponent* ARswBaseCharacter::GetAbilitySystemComponent() const
{
    return GetRswAbilitySystemComponent();
}

void ARswBaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    if (RswAbilitySystemComponent)
    {
        RswAbilitySystemComponent->InitAbilityActorInfo(this, this);
    }
}

