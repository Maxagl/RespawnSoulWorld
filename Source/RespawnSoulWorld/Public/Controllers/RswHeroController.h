// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "RswHeroController.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API ARswHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	ARswHeroController();

	//~ Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface

private:
	FGenericTeamId HeroTeamID;
};
