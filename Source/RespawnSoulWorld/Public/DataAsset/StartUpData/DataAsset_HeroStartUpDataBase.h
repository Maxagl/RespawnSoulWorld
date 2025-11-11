// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "RswTypes/RswStructTypes.h"
#include "DataAsset_HeroStartUpDataBase.generated.h"


/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UDataAsset_HeroStartUpDataBase : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
public:
    virtual void GiveToAbilitySystemComponent(URswAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
    TArray<FRswHeroAbilitySet> HeroStartUpAbilitySets;
	
};
