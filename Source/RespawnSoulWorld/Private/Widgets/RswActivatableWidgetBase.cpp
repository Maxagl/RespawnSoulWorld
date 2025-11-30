// Zhaobang Liu All Rights Reserved

#include "Widgets/RswActivatableWidgetBase.h"

#include "Controllers/FrontEndPlayerController.h"

AFrontEndPlayerController* URswActivatableWidgetBase::GetOwningFrontendPlayerController()
{
	if (!CachedOwningFrontendPC.IsValid())
	{
		CachedOwningFrontendPC = GetOwningPlayer<AFrontEndPlayerController>();
	}

	return CachedOwningFrontendPC.IsValid() ? CachedOwningFrontendPC.Get() : nullptr;
}
