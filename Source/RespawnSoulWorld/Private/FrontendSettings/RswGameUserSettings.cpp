// Zhaobang Liu All Rights Reserved


#include "FrontendSettings/RswGameUserSettings.h"

URswGameUserSettings::URswGameUserSettings()
	: OverallVolume(1.f)
{
}

URswGameUserSettings* URswGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<URswGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}

void URswGameUserSettings::SetOverallVolume(float InVolume)
{
	OverallVolume = InVolume;

	// The actual logic for controlling the volume goes here
}
