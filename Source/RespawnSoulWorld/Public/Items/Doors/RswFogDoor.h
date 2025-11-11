// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Doors/RswDoorBase.h"
#include "RswFogDoor.generated.h"

class ARswEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterBossArea);
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API ARswFogDoor : public ARswDoorBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintAssignable)
	FOnEnterBossArea OnEnterBossArea;

	virtual void BeginPlay() override;
	virtual void OnDoorCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnDoorCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	void DisableDoorMeshCollision(ARswHeroCharacter* Hero);
	void RedirectHeroToFogDoor(ARswHeroCharacter* Hero);
	UFUNCTION()
	void EnableDoorMeshCollision();
	UFUNCTION()
	void HandleBossDead();


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ARswEnemyCharacter* LinkedBoss;



private:
	UPROPERTY()
	bool bDoorIsUsed = false;
public:
	UFUNCTION()
	void ResetDoorStatus();
};
