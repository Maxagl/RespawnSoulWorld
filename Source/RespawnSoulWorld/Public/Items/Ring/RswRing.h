// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RswRing.generated.h"

class USphereComponent;
class UNiagaraComponent;
class ARswMovableItem;
class ARswBaseCharacter;
UCLASS()
class RESPAWNSOULWORLD_API ARswRing : public AActor
{
	GENERATED_BODY()
	
public:	
	ARswRing();
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RingVisual;
	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionSphere;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* GustVFX;

	UPROPERTY(BlueprintReadOnly)
	TArray<ARswMovableItem*> OverlappedMoveableItems;

	UPROPERTY(BlueprintReadOnly)
	TArray<ARswBaseCharacter*> OverlappedEnemies;
	UPROPERTY(BlueprintReadWrite)
	bool bExpanding = false;

	float CurrentRadius = 50;
	float TargetRadius = 250;
	float ExpandSpeed = 250;

protected:
	UFUNCTION()
	virtual void OnRingCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	virtual void Tick(float DeltaTime) override;

};
