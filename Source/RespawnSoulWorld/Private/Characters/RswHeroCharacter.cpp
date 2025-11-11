// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RswHeroCharacter.h"

#include "RswPlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "Components/Input/RwsEnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RswGameplayTags.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "DataAsset/StartUpData/DataAsset_HeroStartUpDataBase.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameMode/RswBaseGameMode.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/RswAttributeSet.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Items/Weapons/RswWeaponBase.h"
#include "RswFunctionLibrary.h"
#include "Items/RswCampfire.h"
#include "Components/SkeletalMeshComponent.h"
#include "RswDebugHelper.h"


ARswHeroCharacter::ARswHeroCharacter()
{

	PrimaryActorTick.bCanEverTick = true;


	PrimaryActorTick.bStartWithTickEnabled = false;
	// 角色不跟着controller转动，移动鼠标不会移动角色面向
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());

	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	// Boom会跟着controller转动，移动鼠标，boom就会移动
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	// camera是附属的，所以camera跟着conroller转动，移动鼠标，照相机的位置就会改变
	FollowCamera->bUsePawnControlRotation = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	// 这里决定了你的角色是否根据速度方向来转向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
}

UPawnCombatComponent* ARswHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* ARswHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* ARswHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void ARswHeroCharacter::FakeDie()
{
	bIsDead = true;
	OnHeroDied.Broadcast();
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	ARswWeaponBase* CurrentWeapon = GetPawnCombatComponent()->GetCharacterCurrentEquippedWeapon();
	if (CurrentWeapon)
	{
		CurrentWeapon->SetActorHiddenInGame(true);
		CurrentWeapon->SetActorEnableCollision(false);
	}
}

void ARswHeroCharacter::Respawn()
{
	if (LastUsedCampFire)
	{
		FRotator RespawnRotaion = LastUsedCampFire->GetActorRotation();

		FVector SpawnDistance = LastUsedCampFire->GetActorForwardVector() * 100;
		SetActorLocation(LastUsedCampFire->GetActorLocation() + SpawnDistance + RespawnOffset);
		RespawnRotaion.Yaw = 180 - RespawnRotaion.Yaw;
		RespawnRotaion.Pitch = 0;
		RespawnRotaion.Roll = 0;
		SetActorRotation(RespawnRotaion);
	}
	else
	{
		SetActorLocation(SpawnLocation);
		SetActorRotation(SpawnRotator);
	}

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
		if (CurrentWeapon)
		{
			CurrentWeapon->SetActorHiddenInGame(false);
			CurrentWeapon->SetActorEnableCollision(true);
		}
	}
}

UAbilitySystemComponent* ARswHeroCharacter::GetAbilitySystemComponent() const
{
	if (ARswPlayerState* PS = GetPlayerState<ARswPlayerState>())
	{
		return PS->RswAbilitySystemComponent;
	}

	return nullptr;
}

void ARswHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());

	ARswPlayerState* PS = GetPlayerState<ARswPlayerState>();
	if (PS)
	{
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		if (ASC)
		{
			ASC->InitAbilityActorInfo(PS, this);
		}
	}

	SpawnLocation = GetActorLocation();
	SpawnRotator = GetActorRotation();
	if (GetRswAbilitySystemComponent() && GetRswAttributeSet())
	{
		if (!CharacterStartUpData.IsNull())
		{
			if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
			{
				int32 AbilityApplyLevel = 1;

				if (ARswBaseGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<ARswBaseGameMode>())
				{
					switch (BaseGameMode->GetCurrentGameDifficulty())
					{
					case ERswGameDifficulty::Easy:
						AbilityApplyLevel = 4;
						// Debug::Print(TEXT("Current Difficulty: Easy"));
						break;

					case ERswGameDifficulty::Normal:
						AbilityApplyLevel = 3;
						// Debug::Print(TEXT("Current Difficulty: Normal"));
						break;

					case ERswGameDifficulty::Hard:
						AbilityApplyLevel = 2;
						// Debug::Print(TEXT("Current Difficulty: Hard"));
						break;

					case ERswGameDifficulty::VeryHard:
						AbilityApplyLevel = 1;
						// Debug::Print(TEXT("Current Difficulty: Very Hard"));
						break;

					default:
						break;
					}
				}

				LoadedData->GiveToAbilitySystemComponent(GetRswAbilitySystemComponent(), AbilityApplyLevel);
			}
		}
	}
}

void ARswHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	// Controller->LocalPlayer->Subsystem->AddmappingContext->bindaction
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	URwsEnhancedInputComponent* RswEnhancedInputComponent = CastChecked<URwsEnhancedInputComponent>(PlayerInputComponent);

	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RswGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RswGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RswGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RswGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);
	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RswGameplayTags::InputTag_PickUp_Stones, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStonesStarted);
	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RswGameplayTags::InputTag_EnterDoor, ETriggerEvent::Started, this, &ThisClass::Input_EnterDoorStarted);
	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RswGameplayTags::InputTag_UseCampFire, ETriggerEvent::Started, this, &ThisClass::Input_UseCampfire);


	RswEnhancedInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void ARswHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARswHeroCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (PostEffectMID)
	{
		if (bFadingIn)
		{
			CurrentTime += DeltaSeconds;
			float Alpha = FMath::Clamp(CurrentTime / FadeTime, 0.f, 0.8f);
			PostEffectMID->SetScalarParameterValue("Intensity", Alpha);

			if (Alpha >= 0.8f)
			{
				bFadingIn = false;
				CurrentTime = 0.f;
				GetWorldTimerManager().SetTimer(FadeOutTimer, this, &ThisClass::StartFadeOut, EffectDuration, false);
			}
		}
		else if (bFadingOut)
		{
			CurrentTime += DeltaSeconds;
			float Alpha = FMath::Clamp(1.f - (CurrentTime / FadeTime), 0.f, 0.8f);
			PostEffectMID->SetScalarParameterValue("Intensity", Alpha);

			if (Alpha <= 0.f)
			{
				bFadingOut = false;
				CurrentTime = 0.f;


				// 清理材质（可选）
				FollowCamera->PostProcessSettings.WeightedBlendables.Array.RemoveAll(
					[&](const FWeightedBlendable& Blendable) {
						return Blendable.Object == PostEffectMID;
					});
				PostEffectMID = nullptr;
				PrimaryActorTick.bStartWithTickEnabled = false;
				//Debug::Print(FString("Disable Tick"));
			}
		}
	}
}

void ARswHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (!bIsForcedMoving)
	{
		if (MovementVector.Y != 0.f)
		{
			const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(ForwardDirection, MovementVector.Y);
		}

		if (MovementVector.X != 0.f)
		{
			const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void ARswHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (!bIsForcedMoving)
	{
		if (LookAxisVector.X != 0.f)
		{
			AddControllerYawInput(LookAxisVector.X);
		}

		if (LookAxisVector.Y != 0.f)
		{
			AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}

void ARswHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void ARswHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? RswGameplayTags::Player_Event_SwitchTarget_Right : RswGameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
}

void ARswHeroCharacter::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		RswGameplayTags::Player_Event_ConsumeStones,
		Data
	);
}

void ARswHeroCharacter::Input_EnterDoorStarted(const FInputActionValue& InputActionValue)
{
	if (bCanEnterFogDoor)
	{
		EnterDoorDelegate.Broadcast(this);
		bIsForcedMoving = true;
	}
}

void ARswHeroCharacter::Input_UseCampfire(const FInputActionValue& InputActionValue)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	TriggerCampFireEffect();
	GetRswAttributeSet()->SetCurrentHealth(GetRswAttributeSet()->GetMaxHealth());
	GetRswAttributeSet()->SetGreyHealth(GetRswAttributeSet()->GetMaxHealth());
	GetPawnUIComponent()->OnCurrentHealthChanged.Broadcast(GetRswAttributeSet()->GetCurrentHealth() / GetRswAttributeSet()->GetMaxHealth());
	GetPawnUIComponent()->OnGreyHealthChanged.Broadcast(GetRswAttributeSet()->GetGreyHealth() / GetRswAttributeSet()->GetMaxHealth());

	UseCampfire.Broadcast(this);
}

void ARswHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	GetRswAbilitySystemComponent()->OnAbilityInputPressed(InInputTag);
}

void ARswHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	GetRswAbilitySystemComponent()->OnAbilityInputReleased(InInputTag);
}

void ARswHeroCharacter::TriggerCampFireEffect()
{
	if (!PostEffectMID && PostEffectMaterial)
	{
		PostEffectMID = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, PostEffectMaterial);
		FollowCamera->PostProcessSettings.WeightedBlendables.Array.Add(FWeightedBlendable(1.0f, PostEffectMID));
	}
	bFadingIn = true;
	CurrentTime = 0.f;
	PostEffectMID->SetScalarParameterValue(FName("Intensity"), 0.f);
}

void ARswHeroCharacter::StartFadeOut()
{
	bFadingOut = true;
	CurrentTime = 0.f;
}

URswAbilitySystemComponent* ARswHeroCharacter::GetRswAbilitySystemComponent() const
{
	if (ARswPlayerState* PS = GetPlayerState<ARswPlayerState>())
	{
		return PS->RswAbilitySystemComponent;
	}

	return nullptr;
}

URswAttributeSet* ARswHeroCharacter::GetRswAttributeSet() const
{
	if (ARswPlayerState* PS = GetPlayerState<ARswPlayerState>())
	{
		return PS->RswAttributeSet;
	}

	return nullptr;
}
