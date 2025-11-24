// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushSoftWidget.generated.h"

class URswActivatableWidgetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, URswActivatableWidgetBase*, PushedWidget);

UCLASS()
class RESPAWNSOULWORLD_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", GameplayTagFilter = "Frontend.WidgetStack", BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget To Widget Stack"))
	static UAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
		APlayerController*											  OwningPlayerController,
		TSoftClassPtr<URswActivatableWidgetBase>					  InSoftWidgetClass,
		FGameplayTag												  InWidgetStackTag,
		bool														  bFocusOnNewlyPushedWidget = true);

	//~ Begin UBlueprintAsyncActionBase Interface
	virtual void Activate() override;
	//~ End UBlueprintAsyncActionBase Interface

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;

private:
	TWeakObjectPtr<UWorld>					 CachedOwningWorld;
	TWeakObjectPtr<APlayerController>		 CachedOwningPC;
	TSoftClassPtr<URswActivatableWidgetBase> CachedSoftWidgetClass;
	FGameplayTag							 CachedWidgetStackTag;
	bool									 bCachedFocusOnNewlyPushedWidget = false;
};
