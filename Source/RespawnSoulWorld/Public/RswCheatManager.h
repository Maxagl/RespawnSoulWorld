// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "RswCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URswCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	void AddWindMastery();
	UFUNCTION(Exec)
	void ForceGust(float Force);
	UFUNCTION(Exec)
	void ResetRingCoolDown();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cheats")
	TSubclassOf<AActor> ActorToSpawn;

};
