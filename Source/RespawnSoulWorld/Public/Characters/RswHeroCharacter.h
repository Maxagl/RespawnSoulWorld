// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RswBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "RswHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UHeroCombatComponent;
class UHeroUIComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressEnterDoor, ARswHeroCharacter*, Hero);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUseCampfire, ARswHeroCharacter*, Hero);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHeroDied);
/**
 *
 */
UCLASS()
class RESPAWNSOULWORLD_API ARswHeroCharacter : public ARswBaseCharacter
{
	GENERATED_BODY()
public:
	ARswHeroCharacter();
	FOnPressEnterDoor EnterDoorDelegate;
	FOnUseCampfire UseCampfire;
	FOnHeroDied OnHeroDied;
	//~ Begin PawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface Interface

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UHeroUIComponent* GetHeroUIComponent() const override;
	//~ End IPawnUIInterface Interface
	virtual void FakeDie() override;
	virtual void Respawn() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:
	// ~Begin Apawn Interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ~End Apawn Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForceMoving")
	bool bIsForcedMoving = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForceMoving")
	FVector VisibleAnywhere = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForceMoving")
	float ForceMovingSpeed = 200;

	UPROPERTY(EditAnywhere, Category = "ForceMoving")
	class ARswCampfire* LastUsedCampFire;

	UPROPERTY(EditAnywhere, Category = "Respawn")
	FVector RespawnOffset = FVector::ZeroVector;



private:
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UHeroUIComponent* HeroUIComponent;

	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;

	bool bCanEnterFogDoor = false;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_PickUpStonesStarted(const FInputActionValue& InputActionValue);
	void Input_EnterDoorStarted(const FInputActionValue& InputActionValue);
	void Input_UseCampfire(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

protected:

	FTimerHandle FadeOutTimer;
	float EffectDuration = 1.f;
	float FadeTime = 1.f;
	float CurrentTime = 0.f;
	bool bFadingIn = false;
	bool bFadingOut = false;

	FTimerHandle ChargeTimerHandle;
	float ChargeTime = 0.0f;
	float MaxChargeTime = 3.0f;
	bool bIsCharging = false;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PostEffectMaterial")
	UMaterialInterface* PostEffectMaterial;
	UPROPERTY()
	UMaterialInstanceDynamic* PostEffectMID;

	void TriggerCampFireEffect();
	void StartFadeOut();

public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
	FORCEINLINE void SetCanEnterFogDoor(bool isOverlappping) { bCanEnterFogDoor = isOverlappping; }

	virtual URswAbilitySystemComponent* GetRswAbilitySystemComponent() const;

	virtual URswAttributeSet* GetRswAttributeSet() const;
};
