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
#include "AIController.h"
#include "Controllers/RswAIController.h"
#include "RswFunctionLibrary.h"
#include "RswGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"
#include "Items//Weapons/RswWeaponBase.h"
#include "AbilitySystem/RswAttributeSet.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "RswFunctionLibrary.h"
#include "Items/Doors/RswFogDoor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RswFunctionLibrary.h"

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

    RswAbilitySystemComponent = CreateDefaultSubobject<URswAbilitySystemComponent>(TEXT("RswAbilitySystemComponent"));
    RswAttributeSet = CreateDefaultSubobject<URswAttributeSet>(TEXT("AttributeSet"));

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

UAbilitySystemComponent* ARswEnemyCharacter::GetAbilitySystemComponent() const
{
    return RswAbilitySystemComponent;
}

void ARswEnemyCharacter::HandleHeroEnterBossArea()
{
   ARswAIController* BossAIController = Cast<ARswAIController>(GetController());
   if (BossAIController)
   {
       BossAIController->RunBehaviorTree(BossAIController->BehaviorTreeAsset);
       URswFunctionLibrary::AddGameplayTagToActorIfNone(this, RswGameplayTags::Enemy_Boss_Event_EnterFogDoor);
   }
   
}

void ARswEnemyCharacter::BossDiedDestroyDoor()
{
     OnBossDead.Broadcast();
}

void ARswEnemyCharacter::FakeDie()
{
    bIsDead = true;
    // GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    ARswWeaponBase* CurrentWeapon = GetPawnCombatComponent()->GetCharacterCurrentEquippedWeapon();
    CurrentWeapon->SetActorHiddenInGame(true);
    CurrentWeapon->SetActorEnableCollision(false);
    if (GetController())
    {
        if (ARswAIController* AIC = Cast<ARswAIController>(GetController()))
        {
            if (UBlackboardComponent* BBC = AIC->GetBlackboardComponent())
            {
                BBC->ClearValue("TargetActor");
            }
        }
        if (UBrainComponent* Brain = Cast<AAIController>(GetController())->BrainComponent)
        {
            Brain->StopLogic(TEXT("Dead"));
        }


    }
}

void ARswEnemyCharacter::Respawn()
{
    SetActorLocation(SpawnLocation);
    SetActorRotation(SpawnRotator);
    if (GetRswAttributeSet()->GetMaxHealth() != GetRswAttributeSet()->GetCurrentHealth())
    {
        GetRswAttributeSet()->SetCurrentHealth(GetRswAttributeSet()->GetMaxHealth());
        GetRswAttributeSet()->SetGreyHealth(GetRswAttributeSet()->GetMaxHealth());
        GetPawnUIComponent()->OnCurrentHealthChanged.Broadcast(GetRswAttributeSet()->GetCurrentHealth() / GetRswAttributeSet()->GetMaxHealth());
        GetPawnUIComponent()->OnGreyHealthChanged.Broadcast(GetRswAttributeSet()->GetGreyHealth() / GetRswAttributeSet()->GetMaxHealth());
    }
    if (bIsDead)
    {
        URswFunctionLibrary::RemoveGameplayTagFromActorIfFound(this, RswGameplayTags::Shared_Status_Dead);
        bIsDead = false;
        SetActorHiddenInGame(false);
        SetActorEnableCollision(true);
        ARswWeaponBase* CurrentWeapon = GetPawnCombatComponent()->GetCharacterCurrentEquippedWeapon();
        CurrentWeapon->SetActorHiddenInGame(false);
        CurrentWeapon->SetActorEnableCollision(true);
        if (ARswAIController* AIC = Cast<ARswAIController>(GetController()))
        {
            if (UBlackboardComponent* BBC = AIC->GetBlackboardComponent())
            {
                BBC->ClearValue("TargetActor");
            }
            UBrainComponent* Brain = AIC->BrainComponent;
            Brain->RestartLogic();
            if (AIC->RunBehaviorTree(AIC->BehaviorTreeAsset))
            {
                UE_LOG(LogTemp, Warning, TEXT("Behavior Tree started successfully."));
            }
            if (UAIPerceptionComponent* Perception = AIC->GetPerceptionComponent())
            {
                Perception->RequestStimuliListenerUpdate(); // Ç¿ÖÆË¢ÐÂ
            }
        }
    }
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
    RswAbilitySystemComponent->InitAbilityActorInfo(this, this);
    SpawnLocation = GetActorLocation();
    SpawnRotator = GetActorRotation();
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

void ARswEnemyCharacter::ResetStatus()
{
    URswFunctionLibrary::RemoveGameplayTagFromActorIfFound(this, RswGameplayTags::Enemy_Boss_Event_EnterFogDoor);
    if (ARswAIController* AIC = Cast<ARswAIController>(GetController()))
    {
        if (UBrainComponent* Brain = AIC->BrainComponent)
        {
            Brain->StopLogic(TEXT("Dead"));
        }
        
        if (UBlackboardComponent* BBC = AIC->GetBlackboardComponent())
        {
            BBC->ClearValue("TargetActor");
            BBC->ClearValue("DistToTarget");
            BBC->ClearValue("HasSpawnedEnemies");
        }
    }
    FTimerHandle TempHandle;

    GetWorld()->GetTimerManager().SetTimer(TempHandle, [this]() {
        GetRswAttributeSet()->SetCurrentHealth(GetRswAttributeSet()->GetMaxHealth());
        GetRswAttributeSet()->SetGreyHealth(GetRswAttributeSet()->GetMaxHealth());
        SetActorLocation(SpawnLocation);
        SetActorRotation(SpawnRotator);}, 5.0f, false);
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
                    LoadedData->GiveToAbilitySystemComponent(GetRswAbilitySystemComponent(), AbilityApplyLevel);

                    // Debug::Print(TEXT("Enemy Start Up Data Loaded"), FColor::Green);
                }
            }
        )
    );
}

URswAbilitySystemComponent* ARswEnemyCharacter::GetRswAbilitySystemComponent() const
{
    return RswAbilitySystemComponent;
}

URswAttributeSet* ARswEnemyCharacter::GetRswAttributeSet() const
{
    return RswAttributeSet;
}
