// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Doors/RswFogDoor.h"
#include "Characters/RswHeroCharacter.h"
#include "RswFunctionLibrary.h"
#include "RswGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "Characters/RswEnemyCharacter.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "RswGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Components/UI/EnemyUIComponent.h"
#include "RswDebugHelper.h"
void ARswFogDoor::BeginPlay()
{
	Super::BeginPlay();
	if (LinkedBoss)
	{
		LinkedBoss->OnBossDead.AddDynamic(this, &ThisClass::HandleBossDead);
		OnEnterBossArea.AddDynamic(LinkedBoss, &ARswEnemyCharacter::HandleHeroEnterBossArea);
	}
	
}
void ARswFogDoor::OnDoorCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (ARswHeroCharacter* Hero = Cast<ARswHeroCharacter>(OtherActor))
	{
		// Debug::Print(TEXT("OnDoorCollisionBoxBeginOverlap - bind start"));
		Hero->SetCanEnterFogDoor(true && !bDoorIsUsed);
		if (!bDoorIsUsed)
		{
			Hero->EnterDoorDelegate.RemoveAll(this);
			Hero->EnterDoorDelegate.AddDynamic(this, &ThisClass::DisableDoorMeshCollision);
			Hero->EnterDoorDelegate.AddDynamic(this, &ThisClass::SpawnSound);
			Hero->GetHeroUIComponent()->OnDoorInteracted.Broadcast(true);
		}
		// 检查Delegate绑定的方法
		//for (const UObject* Obj : Hero->EnterDoorDelegate.GetAllObjects())
		//{
		//	if (Obj)
		//	{
		//		Debug::Print(*Obj->GetName());
		//	}
		//}
		
	}
}

void ARswFogDoor::OnDoorCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARswHeroCharacter* Hero = Cast<ARswHeroCharacter>(OtherActor))
	{
		// Debug::Print(TEXT("Unbind"));
		Hero->SetCanEnterFogDoor(false);
		Hero->GetHeroUIComponent()->OnDoorInteracted.Broadcast(false);
		Hero->EnterDoorDelegate.RemoveAll(this);
		Hero->bIsForcedMoving = false;
	}
	EnableDoorMeshCollision();
}

void ARswFogDoor::DisableDoorMeshCollision(ARswHeroCharacter* Hero)
{
	
	if (!bDoorIsUsed)
	{
		bDoorIsUsed = true; 
		DoorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RedirectHeroToFogDoor(Hero);
		Hero->GetHeroUIComponent()->OnDoorInteracted.Broadcast(false);
		if (LinkedBoss)
		{
			FGameplayTagContainer AbilityTags{};
			AbilityTags.AddTag(RswGameplayTags::Enemy_Boss_Ability_DrawWidget);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimerForNextTick([this, AbilityTags]
			{
				LinkedBoss->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(AbilityTags);
			});
			OnEnterBossArea.Broadcast();
		}
	}
}

void ARswFogDoor::RedirectHeroToFogDoor(ARswHeroCharacter* Hero)
{
	Hero->OnHeroDied.RemoveAll(LinkedBoss->GetEnemyUIComponent());
	Hero->OnHeroDied.RemoveAll(LinkedBoss);
	Hero->OnHeroDied.RemoveAll(this);
	Hero->OnHeroDied.AddDynamic(LinkedBoss->GetEnemyUIComponent(), &UEnemyUIComponent::HideUI);
	Hero->OnHeroDied.AddDynamic(LinkedBoss, &ARswEnemyCharacter::ResetStatus);
	Hero->OnHeroDied.AddDynamic(this, &ThisClass::ResetDoorStatus);

	// 这里找到的是，从start，到end这个方向的世界坐标类的旋转角度
	// 我们要一直看向锁定敌人的花，就转到这个方向就好了
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
		Hero->GetActorLocation(),
		this->GetActorLocation()
	);
	const FRotator DoorRotator = this->GetActorRotation();
	const FRotator CurrentControlRot = Hero->GetControlRotation();
	const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, FRotator(CurrentControlRot.Pitch, -DoorRotator.Yaw, CurrentControlRot.Roll), 1, 1);

	Hero->GetController()->SetControlRotation(TargetRot);
	Hero->SetActorRotation(FRotator(0.f, -DoorRotator.Yaw, 0.f));
}

void ARswFogDoor::EnableDoorMeshCollision()
{
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ARswFogDoor::HandleBossDead()
{
	Destroy();
}

void ARswFogDoor::ResetDoorStatus()
{
	bDoorIsUsed = false;
}

