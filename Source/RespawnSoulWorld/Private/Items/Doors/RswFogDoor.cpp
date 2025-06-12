// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Doors/RswFogDoor.h"
#include "Characters/RswHeroCharacter.h"

#include "RswDebugHelper.h"


void ARswFogDoor::OnDoorCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (ARswHeroCharacter* Hero = Cast<ARswHeroCharacter>(OtherActor))
	{
		Debug::Print(TEXT("OnDoorCollisionBoxBeginOverlap - bind start"));
		Hero->EnterDoorDelegate.RemoveAll(this);
		Hero->EnterDoorDelegate.AddDynamic(this, &ThisClass::DisableDoorMeshCollision);
		for (const UObject* Obj : Hero->EnterDoorDelegate.GetAllObjects())
		{
			if (Obj)
			{
				Debug::Print(*Obj->GetName());
			}
		}
		
	}
}

void ARswFogDoor::OnDoorCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARswHeroCharacter* Hero = Cast<ARswHeroCharacter>(OtherActor))
	{
		Debug::Print(TEXT("Unbind"));
		Hero->EnterDoorDelegate.RemoveAll(this);
	}
	EnableDoorMeshCollision();
}

void ARswFogDoor::DisableDoorMeshCollision()
{
	Debug::Print(TEXT("Disable collision"));
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ECollisionEnabled::Type CollisionStatus = DoorMesh->GetCollisionEnabled();
	FString StatusString;
	Debug::Print(TEXT("current status: " + StatusString));
	switch (CollisionStatus)
	{
	case ECollisionEnabled::NoCollision:
		StatusString = TEXT("NoCollision");
		break;
	case ECollisionEnabled::QueryOnly:
		StatusString = TEXT("QueryOnly");
		break;
	case ECollisionEnabled::PhysicsOnly:
		StatusString = TEXT("PhysicsOnly");
		break;
	case ECollisionEnabled::QueryAndPhysics:
		StatusString = TEXT("QueryAndPhysics");
		break;
	default:
		StatusString = TEXT("Unknown");
		break;
	}
	//DoorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//CollisionStatus = DoorMesh->GetCollisionEnabled();
	//StatusString;
	//Debug::Print(TEXT("current status: " + StatusString));
	//switch (CollisionStatus)
	//{
	//case ECollisionEnabled::NoCollision:
	//	StatusString = TEXT("NoCollision");
	//	break;
	//case ECollisionEnabled::QueryOnly:
	//	StatusString = TEXT("QueryOnly");
	//	break;
	//case ECollisionEnabled::PhysicsOnly:
	//	StatusString = TEXT("PhysicsOnly");
	//	break;
	//case ECollisionEnabled::QueryAndPhysics:
	//	StatusString = TEXT("QueryAndPhysics");
	//	break;
	//default:
	//	StatusString = TEXT("Unknown");
	//	break;
	//}
	//Debug::Print(TEXT("current status: " + StatusString));
	
}

void ARswFogDoor::EnableDoorMeshCollision()
{
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
