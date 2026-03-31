// Zhaobang Liu All Rights Reserved


#include "FrontendSettings/RswGameUserSettings.h"

URswGameUserSettings::URswGameUserSettings()
	: OverallVolume(1.f)
	, MusicVolume(1.f)
	, SoundFXVolume(1.f)
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

void URswGameUserSettings::SetMusicVolume(float InVolume)
{
	MusicVolume = InVolume;
}

void URswGameUserSettings::SetSoundFXVolume(float InVolume)
{
	SoundFXVolume = InVolume;
}
