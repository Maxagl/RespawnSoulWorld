// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Ring/RswRing.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Items/MovableItem/RswMovableItem.h"
#include "Characters/RswEnemyCharacter.h"
#include "RswDebugHelper.h"

// Sets default values
ARswRing::ARswRing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	SetRootComponent(CollisionSphere);
	CollisionSphere->InitSphereRadius(10.f); // 初始小点
	CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnRingCollisionSphereBeginOverlap);

	RingVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RingVisual"));
	RingVisual->SetupAttachment(RootComponent);
	RingVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 特效组件
	GustVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("GustVFX"));
	GustVFX->SetupAttachment(RootComponent);
}

void ARswRing::OnRingCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARswEnemyCharacter* Enemy = Cast<ARswEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.AddUnique(Enemy);
	}
	if (ARswMovableItem* MovableItem = Cast<ARswMovableItem>(OtherActor))
	{
		OverlappedMoveableItems.AddUnique(MovableItem);
	}
}

void ARswRing::Tick(float DeltaTime)
{
	if (bExpanding)
	{
		CurrentRadius += ExpandSpeed * DeltaTime;
		CollisionSphere->SetSphereRadius(CurrentRadius);
		// 视觉同步：根据半径设置缩放
		GustVFX->SetVectorParameter(TEXT("CylinderRadius"), FVector(CurrentRadius / 100.f, CurrentRadius / 100.f, 1.f));

		if (CurrentRadius >= TargetRadius)
		{
			bExpanding = false;
		}
	}
}

