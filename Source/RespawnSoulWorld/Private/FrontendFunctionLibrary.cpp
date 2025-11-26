// Zhaobang Liu All Rights Reserved


#include "FrontendFunctionLibrary.h"
#include "FrontendSettings/FrontEndDeveloperSettings.h"

TSoftClassPtr<URswActivatableWidgetBase> UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(FGameplayTag InWidgetTag)
{
	const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();

	checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());

	return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);
}
