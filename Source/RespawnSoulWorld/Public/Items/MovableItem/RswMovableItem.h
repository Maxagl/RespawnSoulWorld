// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RswGameplayTags.h"
#include "GameplayTagAssetInterface.h"
#include "RswMovableItem.generated.h"

class USphereComponent;

UCLASS()
class RESPAWNSOULWORLD_API ARswMovableItem : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARswMovableItem();

protected:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer MyGameplayTags;

    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

    virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;

	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

};
