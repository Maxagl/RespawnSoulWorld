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
	//***** Audio Collection Tab ***** //

private:
	UPROPERTY(Config)
	FString CurrentGameDifficulty;

	//***** Audio Collection Tab ***** //
	UPROPERTY(Config)
	float OverallVolume;
	//***** Audio Collection Tab ***** //
};
