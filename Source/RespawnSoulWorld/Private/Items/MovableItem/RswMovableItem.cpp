// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/MovableItem/RswMovableItem.h"
#include "Components/SphereComponent.h"

// Sets default values
ARswMovableItem::ARswMovableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->InitSphereRadius(50.f); // ³õÊ¼Ð¡µã
	CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionSphere->SetupAttachment(RootComponent);
	

}


// Called every frame
void ARswMovableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARswMovableItem::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = MyGameplayTags;
}

bool ARswMovableItem::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return MyGameplayTags.HasTag(TagToCheck);
}

bool ARswMovableItem::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return MyGameplayTags.HasAny(TagContainer);
}

bool ARswMovableItem::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return MyGameplayTags.HasAll(TagContainer);
}

