// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "RswActivatableWidgetBase.generated.h"

class AFrontEndPlayerController;
UCLASS()
class RESPAWNSOULWORLD_API URswActivatableWidgetBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	AFrontEndPlayerController* GetOwningFrontendPlayerController();

private:
	TWeakObjectPtr<AFrontEndPlayerController> CachedOwningFrontendPC;
};
