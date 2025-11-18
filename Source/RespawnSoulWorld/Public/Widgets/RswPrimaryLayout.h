// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "RswPrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;
/**
 *
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class RESPAWNSOULWORLD_API URswPrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InTag) const;

protected:
	UFUNCTION(BlueprintCallable, meta = (GameplayTagFilter="Frontend.WidgetStack"))
	void RegisterWidgetStack(FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack);

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
