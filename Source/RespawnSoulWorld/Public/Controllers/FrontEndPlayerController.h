// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontEndPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API AFrontEndPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	//~ Begin APlayerController Interface
	virtual void OnPossess(APawn* InPawn) override;
	//~ End APlayerController Interface
};
