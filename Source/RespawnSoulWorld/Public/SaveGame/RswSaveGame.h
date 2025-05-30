// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RswTypes/RswEnumTypes.h"

#include "RswSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	ERswGameDifficulty SavedCurrentGameDifficulty;
};
