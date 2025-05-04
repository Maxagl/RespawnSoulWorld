// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "RswAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
    URswAttributeSet();

    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData CurrentHealth;
    ATTRIBUTE_ACCESSORS(URswAttributeSet, CurrentHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(URswAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Rage")
    FGameplayAttributeData CurrentRage;
    ATTRIBUTE_ACCESSORS(URswAttributeSet, CurrentRage)

    UPROPERTY(BlueprintReadOnly, Category = "Rage")
    FGameplayAttributeData MaxRage;
    ATTRIBUTE_ACCESSORS(URswAttributeSet, MaxRage)

    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(URswAttributeSet, AttackPower)

    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData DefensePower;
    ATTRIBUTE_ACCESSORS(URswAttributeSet, DefensePower)

    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData DamageTaken;
    ATTRIBUTE_ACCESSORS(URswAttributeSet, DamageTaken)
};
