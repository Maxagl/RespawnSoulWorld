// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Doors/RswDoorBase.h"
#include "RswFogDoor.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API ARswFogDoor : public ARswDoorBase
{
	GENERATED_BODY()
protected:
	
	virtual void OnDoorCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnDoorCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	void DisableDoorMeshCollision();
	UFUNCTION()
	void EnableDoorMeshCollision();
};
