// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RswTypes/RswEnumTypes.h"
#include "RswBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API ARswBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ARswBaseGameMode();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	ERswGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE ERswGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};
