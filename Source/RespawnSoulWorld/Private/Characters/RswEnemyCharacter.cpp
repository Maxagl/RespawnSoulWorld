// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RswEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/RswWidgetBase.h"
#include "Components/BoxComponent.h"
#include "RswFunctionLibrary.h"
#include "GameMode/RswBaseGameMode.h"

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

    LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
    LeftHandCollisionBox->SetupAttachment(GetMesh());
    LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

    RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
    RightHandCollisionBox->SetupAttachment(GetMesh());
    RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

    LeftLegCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftLegCollisionBox");
    LeftLegCollisionBox->SetupAttachment(GetMesh());
    LeftLegCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LeftLegCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

    RightLegCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightLegCollisionBox");
    RightLegCollisionBox->SetupAttachment(GetMesh());
    RightLegCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RightLegCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
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

#if WITH_EDITOR
void ARswEnemyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
    {
        LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
    }

    if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
    {
        RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
    }

    if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftLegCollisionBoxAttachBoneName))
    {
        LeftLegCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftLegCollisionBoxAttachBoneName);
    }

    if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightLegCollisionBoxAttachBoneName))
    {
        RightLegCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightLegCollisionBoxAttachBoneName);
    }
}
#endif

void ARswEnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (APawn* HitPawn = Cast<APawn>(OtherActor))
    {
        if (URswFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
        {
            EnemyCombatComponent->OnHitTargetActor(HitPawn);
        }
    }
}

void ARswEnemyCharacter::InitEnemyStartUpData()
{
    if (CharacterStartUpData.IsNull())
    {
        return;
    }
    int32 AbilityApplyLevel = 1;

    if (ARswBaseGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<ARswBaseGameMode>())
    {
        switch (BaseGameMode->GetCurrentGameDifficulty())
        {
        case ERswGameDifficulty::Easy:
            AbilityApplyLevel = 1;
            break;

        case ERswGameDifficulty::Normal:
            AbilityApplyLevel = 2;
            break;

        case ERswGameDifficulty::Hard:
            AbilityApplyLevel = 3;
            break;

        case ERswGameDifficulty::VeryHard:
            AbilityApplyLevel = 4;
            break;

        default:
            break;
        }
    }
    UAssetManager::GetStreamableManager().RequestAsyncLoad(
        CharacterStartUpData.ToSoftObjectPath(),
        FStreamableDelegate::CreateLambda(
            [this, AbilityApplyLevel]()
            {
                if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
                {
                    LoadedData->GiveToAbilitySystemComponent(RswAbilitySystemComponent, AbilityApplyLevel);

                    // Debug::Print(TEXT("Enemy Start Up Data Loaded"), FColor::Green);
                }
            }
        )
    );
}
