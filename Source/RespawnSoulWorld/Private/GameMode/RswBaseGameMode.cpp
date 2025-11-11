// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/RswBaseGameMode.h"

#include "RswPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

ARswBaseGameMode::ARswBaseGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PlayerStateClass = ARswPlayerState::StaticClass();
}

void ARswBaseGameMode::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{

	Super::GetSeamlessTravelActorList(bToTransition, ActorList);
	ActorList.Add(GameState->PlayerArray[0]->GetPlayerController());
}
