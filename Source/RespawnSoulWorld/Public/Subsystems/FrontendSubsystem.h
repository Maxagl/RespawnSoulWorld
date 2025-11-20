// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendSubsystem.generated.h"

struct FGameplayTag;

class URswPrimaryLayout;
class URswActivatableWidgetBase;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

UCLASS()
class RESPAWNSOULWORLD_API UFrontendSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UFrontendSubsystem* Get(const UObject* WorldContextObject);

	//~ Begin USubsystem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ End USubsystem Interface

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(URswPrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<URswActivatableWidgetBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, URswActivatableWidgetBase*)> AysncPushStateCallback);

private:
	UPROPERTY(Transient)
	URswPrimaryLayout* CreatedPrimaryLayout;
};
