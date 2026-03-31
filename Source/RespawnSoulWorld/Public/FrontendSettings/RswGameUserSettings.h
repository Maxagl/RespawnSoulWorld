// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "RswGameUserSettings.generated.h"

/**
 *
 */
UCLASS()
class RESPAWNSOULWORLD_API URswGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:
	URswGameUserSettings();

	static URswGameUserSettings* Get();

	//***** Gameplay Collection Tab ***** //
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }

	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InNewDifficulty) { CurrentGameDifficulty = InNewDifficulty; }
	//***** Gameplay Collection Tab ***** //

	//***** Audio Collection Tab ***** //
	UFUNCTION()
	float GetOverallVolume() const { return OverallVolume; }

	UFUNCTION()
	void SetOverallVolume(float InVolume);

	UFUNCTION()
	float GetMusicVolume() const { return MusicVolume; }

	UFUNCTION()
	void SetMusicVolume(float InVolume);

	UFUNCTION()
	float GetSoundFXVolume() const { return SoundFXVolume; }

	UFUNCTION()
	void SetSoundFXVolume(float InVolume);
	//***** Audio Collection Tab ***** //

private:
	UPROPERTY(Config)
	FString CurrentGameDifficulty;

	//***** Audio Collection Tab ***** //
	UPROPERTY(Config)
	float OverallVolume;

	UPROPERTY(Config)
	float MusicVolume;

	UPROPERTY(Config)
	float SoundFXVolume;
	//***** Audio Collection Tab ***** //
};
