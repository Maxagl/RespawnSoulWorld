// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "FrontEndDeveloperSettings.generated.h"

class URswActivatableWidgetBase;

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Frontend UI Settings"))
class RESPAWNSOULWORLD_API UFrontEndDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "Frontend.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<URswActivatableWidgetBase>> FrontendWidgetMap;
};
