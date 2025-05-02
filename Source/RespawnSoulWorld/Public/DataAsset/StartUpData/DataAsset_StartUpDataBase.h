// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class URswGameplayAbility;
class URswAbilitySystemComponent;

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
    virtual void GiveToAbilitySystemComponent(URswAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
    TArray< TSubclassOf < URswGameplayAbility > > ActivateOnGivenAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
    TArray< TSubclassOf < URswGameplayAbility > > ReactiveAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
    TArray< TSubclassOf < UGameplayEffect > > StartUpGameplayEffects;

    void GrantAbilities(const TArray< TSubclassOf < URswGameplayAbility > >& InAbilitiesToGive, URswAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
