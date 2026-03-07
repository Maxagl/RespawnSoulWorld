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
	static URswGameUserSettings* Get();

    //***** Gameplay Collection Tab ***** //
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }

	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InNewDifficulty) { CurrentGameDifficulty = InNewDifficulty; }
	//***** Gameplay Collection Tab ***** //

private:
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
};
