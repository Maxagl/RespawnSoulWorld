// Zhaobang Liu All Rights Reserved


#include "FrontendFunctionLibrary.h"
#include "FrontendSettings/FrontEndDeveloperSettings.h"

TSoftClassPtr<URswActivatableWidgetBase> UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(FGameplayTag InWidgetTag)
{
	const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();

	checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());

	return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);
}

TSoftObjectPtr<UTexture2D> UFrontendFunctionLibrary::GetOptionsSoftImageByTag(UPARAM(meta = (Categories = "Frontend.Image")) FGameplayTag InImageTag)
{
	const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();

	checkf(FrontendDeveloperSettings->OptionsScreenSoftImageMap.Contains(InImageTag), TEXT("Could not find an image accociated with tag %s"), *InImageTag.ToString());

	return FrontendDeveloperSettings->OptionsScreenSoftImageMap.FindRef(InImageTag);
}
