// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagcontainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

// ���struct��Ϊ����InputTag��Actionһһ��Ӧ
USTRUCT(BlueprintType)
struct FRswInputActionConfig
{
    GENERATED_BODY()

public:
    // �����categories��Ϊ��ֱ��ѡ��Inputag�����
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
    FGameplayTag InputTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputAction;
};

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FRswInputActionConfig> NativeInputActions;

    UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
};
