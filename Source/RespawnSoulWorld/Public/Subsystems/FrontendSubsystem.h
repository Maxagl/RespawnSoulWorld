// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendSubsystem.generated.h"

struct FGameplayTag;

class URswPrimaryLayout;
class URswCommonButtonBase;
class URswActivatableWidgetBase;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, URswCommonButtonBase*, BroadcastingButton, FText, DescriptionText);

UCLASS()
class RESPAWNSOULWORLD_API UFrontendSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

	static UFrontendSubsystem* Get(const UObject* WorldContextObject);

	//~ Begin USubsystem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ End USubsystem Interface

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(URswPrimaryLayout* InCreatedWidget);

	// InSoftWidgetClass加载完成--> AddWidget（创建Widget实例并调用回调）--> AysncPushStateCallback
	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<URswActivatableWidgetBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, URswActivatableWidgetBase*)> AysncPushStateCallback);

private:
	UPROPERTY(Transient)
	URswPrimaryLayout* CreatedPrimaryLayout;
};
