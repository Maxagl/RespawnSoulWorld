// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/RswCampfire.h"
#include "Components/BoxComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "Characters/RswEnemyCharacter.h"
#include "Characters/RswHeroCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ARswCampfire::ARswCampfire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	SetRootComponent(CollisionBox);
	CampfireMesh = CreateDefaultSubobject<UStaticMeshComponent>("CampfireMesh");
	CampfireMesh->SetupAttachment(CollisionBox);

	CampfireMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CampfireMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCampfireCollisionBoxBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCampfireCollisionBoxEndOverlap);

}

void ARswCampfire::OnCampfireCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARswHeroCharacter* Hero = Cast<ARswHeroCharacter>(OtherActor))
	{
		ULocalPlayer* LocalPlayer = Hero->GetController<APlayerController>()->GetLocalPlayer();
		Hero->UseCampfire.AddDynamic(this, &ThisClass::RespawnEnemy);
		Hero->UseCampfire.AddDynamic(this, &ThisClass::SpawnSound);
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
		Subsystem->AddMappingContext(InputMap, InputMapPriority);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Hero]
			{
				Hero->GetHeroUIComponent()->OnCampfireInteracted.Broadcast(true);
			}, 0.1f, false);
	}
}

void ARswCampfire::OnCampfireCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARswHeroCharacter* Hero = Cast<ARswHeroCharacter>(OtherActor))
	{

		Hero->UseCampfire.RemoveAll(this);

		ULocalPlayer* LocalPlayer = Hero->GetController<APlayerController>()->GetLocalPlayer();

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
		Hero->GetHeroUIComponent()->OnCampfireInteracted.Broadcast(false);
		Subsystem->RemoveMappingContext(InputMap);
	}
}

void ARswCampfire::RespawnEnemy(ARswHeroCharacter* Hero)
{
	Hero->LastUsedCampFire = this;
	for (TActorIterator<ARswEnemyCharacter> It(GetWorld()); It; ++It)
	{
		ARswEnemyCharacter* Enemy = *It;
		Enemy->Respawn();
	}
}

void ARswCampfire::SpawnSound(ARswHeroCharacter* Hero)
{
	if (BonfireSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BonfireSFX, GetActorLocation());
	}
}

