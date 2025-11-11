// Fill out your copyright notice in the Description page of Project Settings.


#include "RswCheatManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "RswFunctionLibrary.h"
#include "RswGameplayTags.h"
#include "Items/Ring/RswRing.h"
#include "Characters/RswHeroCharacter.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/UI/HeroUIComponent.h"
void URswCheatManager::AddWindMastery()
{
	ACharacter* Character = Cast<ACharacter>(GetOuterAPlayerController()->GetPawn());
	URswFunctionLibrary::AddGameplayTagToActorIfNone(Character, RswGameplayTags::Shared_SetByCaller_Buff_WindMastery);
}

void URswCheatManager::ForceGust(float Force)
{
	ACharacter* Character = Cast<ACharacter>(GetOuterAPlayerController()->GetPawn());
	FVector SpawnLocation = Character->GetActorLocation();
	FRotator SpawnRotator = Character->GetActorRotation();
	SpawnLocation.Z = 0;
	
	ARswRing* Ring = GetWorld()->SpawnActor<ARswRing>(ActorToSpawn, SpawnLocation, SpawnRotator);
	float startRadius = Ring->CurrentRadius;
	Ring->CurrentRadius = startRadius + Ring->TargetRadius * Force;
	Ring->CollisionSphere->SetSphereRadius(Ring->CurrentRadius);
	Ring->GustVFX->SetVectorParameter(TEXT("CylinderRadius"), FVector(Ring->CurrentRadius / 100.f, Ring->CurrentRadius / 100.f, 1.f));
}

void URswCheatManager::ResetRingCoolDown()
{
	ARswHeroCharacter* Character = Cast<ARswHeroCharacter>(GetOuterAPlayerController()->GetPawn());
	FGameplayTagContainer TagContatiner;
	TagContatiner.AddTag(RswGameplayTags::Player_Cooldown_RingGust);
	Character->GetHeroUIComponent()->OnCancleAbilityCooldownBegin.Broadcast();
	Character->GetRswAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(TagContatiner);
	
}
