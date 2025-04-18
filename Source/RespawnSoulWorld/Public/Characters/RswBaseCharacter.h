// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RswBaseCharacter.generated.h"

class URswAbilitySystemComponent;
class URswAttributeSet;
UCLASS()
class RESPAWNSOULWORLD_API ARswBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARswBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	URswAbilitySystemComponent* RswAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	URswAttributeSet* RswAttributeSet;

public:
	FORCEINLINE URswAbilitySystemComponent* GetRswAbilitySystemComponent() const { return RswAbilitySystemComponent; }

	FORCEINLINE URswAttributeSet* GetRswAttributeSet() const { return RswAttributeSet; }
};
