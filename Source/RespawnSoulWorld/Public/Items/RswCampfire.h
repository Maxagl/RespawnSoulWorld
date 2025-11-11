// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RswCampfire.generated.h"

class UBoxComponent;

UCLASS()
class RESPAWNSOULWORLD_API ARswCampfire : public AActor
{
	GENERATED_BODY()
	
public:	
	ARswCampfire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Campfire Interaction")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Campfire Interaction")
	UStaticMeshComponent* CampfireMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Campfire Interaction")
	class UInputMappingContext* InputMap;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Campfire Interaction")
	int32 InputMapPriority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
	USoundBase* BonfireSFX;

	UFUNCTION()
	virtual void OnCampfireCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnCampfireCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void RespawnEnemy(ARswHeroCharacter* Hero);

	UFUNCTION()
	void SpawnSound(ARswHeroCharacter* Hero);

	FTimerHandle TimerHandle;
};
