// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/RswActivatableWidgetBase.h"
#include "RswWidget_OptionScreen.generated.h"

/**
 *
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class RESPAWNSOULWORLD_API URswWidget_OptionScreen : public URswActivatableWidgetBase
{
	GENERATED_BODY()

protected:
	//~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface

private:
	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();

	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
};
