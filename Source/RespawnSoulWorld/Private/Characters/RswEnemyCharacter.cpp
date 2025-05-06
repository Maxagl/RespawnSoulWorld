// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RswEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/RswWidgetBase.h"

#include "RswDebugHelper.h"

ARswEnemyCharacter::ARswEnemyCharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

    EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
    EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUIComponent");

    EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComponent");
    EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

UPawnCombatComponent* ARswEnemyCharacter::GetPawnCombatComponent() const
{
    return EnemyCombatComponent;
}

UPawnUIComponent* ARswEnemyCharacter::GetPawnUIComponent() const
{
    return EnemyUIComponent;
}

UEnemyUIComponent* ARswEnemyCharacter::GetEnemyUIComponent() const
{
    return EnemyUIComponent;
}

void ARswEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (URswWidgetBase* HealthWidget = Cast<URswWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
    {
        HealthWidget->InitEnemyCreatedWidget(this);
    }
}

void ARswEnemyCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    InitEnemyStartUpData();
}

void ARswEnemyCharacter::InitEnemyStartUpData()
{
    if (CharacterStartUpData.IsNull())
    {
        return;
    }

    UAssetManager::GetStreamableManager().RequestAsyncLoad(
        CharacterStartUpData.ToSoftObjectPath(),
        FStreamableDelegate::CreateLambda(
            [this]()
            {
                if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
                {
                    LoadedData->GiveToAbilitySystemComponent(RswAbilitySystemComponent);

                    // Debug::Print(TEXT("Enemy Start Up Data Loaded"), FColor::Green);
                }
            }
        )
    );
}
