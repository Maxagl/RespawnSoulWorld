// Zhaobang Liu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/RswActivatableWidgetBase.h"
#include "RswWidget_OptionScreen.generated.h"

class URswCommonListView;
class UOptionsDataRegistry;
class URswTabListWidgetBase;

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

	//~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override; 
	//~ End UCommonActivatableWidget Interface

private:
	UOptionsDataRegistry* GetOrCreateDataRegistry();

	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();

	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);

    void OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered);
	void OnListViewItemSelected(UObject* InSelectedItem);

	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	URswTabListWidgetBase* TabListWidget_OptionsTabs;

	UPROPERTY(meta = (BindWidget))
	URswCommonListView* ListView_OptionsContent;
	//***** Bound Widgets ***** //

	// Handle the creation of data in the options screen. Direct access to this variable is forbidden
	UPROPERTY(Transient)
	UOptionsDataRegistry* CreatedOwningDataRegistry;

	// FDataTableRowHandle 本身是什么类型的Row都可以，但是这里我们指定它是 CommonInputActionDataBase 类型的 Row
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
};
