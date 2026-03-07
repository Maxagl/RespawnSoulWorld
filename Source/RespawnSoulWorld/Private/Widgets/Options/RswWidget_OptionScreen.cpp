// Zhaobang Liu All Rights Reserved

#include "Widgets/Options/RswWidget_OptionScreen.h"

#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "FrontendSettings/RswGameUserSettings.h"
#include "Widgets/Components/RswCommonListView.h"
#include "Widgets/Components/RswTabListWidgetBase.h"
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

    ListView_OptionsContent->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHovered);
	ListView_OptionsContent->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelected);
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

void URswWidget_OptionScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	URswGameUserSettings::Get()->ApplySettings(true);
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

	// 这里的listview设置的Items 对应到OnGenerateEntryWidgetInternal里面的Item
	ListView_OptionsContent->SetListItems(FoundListSourceItems);
	ListView_OptionsContent->RequestRefresh();

	if (ListView_OptionsContent->GetNumItems() != 0)
	{
		ListView_OptionsContent->NavigateToIndex(0);
		ListView_OptionsContent->SetSelectedIndex(0);

	}
}

void URswWidget_OptionScreen::OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered)
{
	if (!InHoveredItem)
	{
		return;
	}

	const FString DebugString =
		CastChecked<UListDataObject_Base>(InHoveredItem)->GetDataDisplayName().ToString() + TEXT(" was ") + (bWasHovered ? TEXT("hovered") : TEXT("unhovered"));

	Debug::Print(DebugString);
}

void URswWidget_OptionScreen::OnListViewItemSelected(UObject* InSelectedItem)
{
	if (!InSelectedItem)
	{
		return;
	}

	const FString DebugString =
		CastChecked<UListDataObject_Base>(InSelectedItem)->GetDataDisplayName().ToString() + TEXT(" was selected");

	Debug::Print(DebugString);
}
