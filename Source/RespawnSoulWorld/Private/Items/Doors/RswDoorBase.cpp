// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Doors/RswDoorBase.h"
#include "Components/BoxComponent.h"
// Sets default values
ARswDoorBase::ARswDoorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	SetRootComponent(CollisionBox);
	DoorMesh->SetupAttachment(CollisionBox);

	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DoorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnDoorCollisionBoxBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnDoorCollisionBoxEndOverlap);
}

void ARswDoorBase::OnDoorCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ARswDoorBase::OnDoorCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

