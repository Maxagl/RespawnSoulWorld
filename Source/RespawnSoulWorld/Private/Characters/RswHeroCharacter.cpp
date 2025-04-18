// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RswHeroCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "Components/Input/RwsEnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RswGameplayTags.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"


#include "RswDebugHelper.h"


ARswHeroCharacter::ARswHeroCharacter()
{
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
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	// 这里决定了你的角色是否根据速度方向来转向
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

void ARswHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (RswAbilitySystemComponent && RswAttributeSet)
	{
		const FString ASCText = FString::Printf(TEXT("Owner Actor: %s, AvatarActor: %s"), *RswAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *RswAbilitySystemComponent->GetAvatarActor()->GetActorLabel());

		Debug::Print(TEXT("Ability system component valid. ") + ASCText, FColor::Green);
		Debug::Print(TEXT("AttributeSet valid. ") + ASCText, FColor::Green);
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

	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RwsGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	RswEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, RwsGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
}

void ARswHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARswHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

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

void ARswHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
