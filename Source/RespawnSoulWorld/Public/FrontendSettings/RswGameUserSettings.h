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

private:
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
};
