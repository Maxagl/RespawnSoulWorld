// Fill out your copyright notice in the Description page of Project Settings.


#include "RswPlayerState.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "AbilitySystem/RswAttributeSet.h"

ARswPlayerState::ARswPlayerState()
{
	RswAbilitySystemComponent = CreateDefaultSubobject<URswAbilitySystemComponent>(TEXT("RswAbilitySystemComponent"));
	RswAttributeSet = CreateDefaultSubobject<URswAttributeSet>(TEXT("AttributeSet"));
}

void ARswPlayerState::BeginPlay()
{
	Super::BeginPlay();


}

UAbilitySystemComponent* ARswPlayerState::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(RswAbilitySystemComponent);
}
