// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FrontendFunctionLibrary.generated.h"

class URswActivatableWidgetBase;

UCLASS()
class RESPAWNSOULWORLD_API UFrontendFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Frontend Function Library", meta = (GameplayTagFilter = "Frontend.Widget"))
	static TSoftClassPtr<URswActivatableWidgetBase> GetFrontendSoftWidgetClassByTag(FGameplayTag InWidgetTag);
};
