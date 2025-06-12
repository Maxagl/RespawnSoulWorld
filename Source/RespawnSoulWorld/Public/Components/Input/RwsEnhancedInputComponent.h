// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "RwsEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API URwsEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
    template<class UserObject, typename CallbackFunc>
    void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);


    template<class UserObject, typename CallbackFunc>
    void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void URwsEnhancedInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
    checkf(InInputConfig, TEXT("Input config data asset is null,can not proceed with binding"));

    if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
    {
        BindAction(FoundAction, TriggerEvent, ContextObject, Func);
    }
}

template<class UserObject, typename CallbackFunc>
inline void URwsEnhancedInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc)
{
    checkf(InInputConfig, TEXT("Input config data asset is null,can not proceed with binding"));

    for (const FRswInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
    {
        if (!AbilityInputActionConfig.IsValid()) continue;
        // �����Դ�룬��ֱ����ģ����ż�
        // ���Լ򵥵����Ϊ������󶨺���Ĳ���������Զ���ӵ�delegate�Ļص���������ȥ����������д�ص�������ʱ��ҲҪ������Щ����
        BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
        BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputRelasedFunc, AbilityInputActionConfig.InputTag);
    }
}
