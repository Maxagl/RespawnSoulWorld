// Zhaobang Liu All Rights Reserved


#include "FrontendSettings/RswGameUserSettings.h"

URswGameUserSettings* URswGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<URswGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}
