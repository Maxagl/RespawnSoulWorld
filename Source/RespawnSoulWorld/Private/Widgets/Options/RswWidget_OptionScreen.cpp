// Zhaobang Liu All Rights Reserved

#include "Widgets/Options/RswWidget_OptionScreen.h"

#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Components/RswTabListWidgetBase.h"
#include "Widgets/Components/RswCommonListView.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

#include "RswDebugHelper.h"

void URswWidget_OptionScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)));
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)));

	TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);
}

void URswWidget_OptionScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (UListDataObject_Collection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if (!TabCollection)
		{
			continue;
		}

		const FName TabID = TabCollection->GetDataID();

		if (TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabID) != nullptr)
		{
			continue;
		}

		TabListWidget_OptionsTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

UOptionsDataRegistry* URswWidget_OptionScreen::GetOrCreateDataRegistry()
{
	if (!CreatedOwningDataRegistry)
	{
		CreatedOwningDataRegistry = NewObject<UOptionsDataRegistry>();
		CreatedOwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}

	checkf(CreatedOwningDataRegistry, TEXT("Data registry for options screen is not valid"));

	return CreatedOwningDataRegistry;
}

void URswWidget_OptionScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered"));
}

void URswWidget_OptionScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void URswWidget_OptionScreen::OnOptionsTabSelected(FName TabId)
{
	TArray<UListDataObject_Base*> FoundListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabId);

	ListView_OptionsContent->SetListItems(FoundListSourceItems);
	ListView_OptionsContent->RequestRefresh();

	if (ListView_OptionsContent->GetNumItems() != 0)
	{
		ListView_OptionsContent->NavigateToIndex(0);
		ListView_OptionsContent->SetSelectedIndex(0);
	}
}
