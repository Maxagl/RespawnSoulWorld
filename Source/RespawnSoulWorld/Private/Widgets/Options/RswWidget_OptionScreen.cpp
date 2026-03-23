// Zhaobang Liu All Rights Reserved

#include "Widgets/Options/RswWidget_OptionScreen.h"

#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"
#include "Subsystems/FrontendSubsystem.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "FrontendSettings/RswGameUserSettings.h"
#include "Widgets/Components/RswCommonListView.h"
#include "Widgets/Components/RswCommonButtonBase.h"
#include "Widgets/Components/RswTabListWidgetBase.h"
#include "Widgets/Options/Widget_OptionsDetailView.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
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

UWidget* URswWidget_OptionScreen::NativeGetDesiredFocusTarget() const
{
	if (UObject* SelectedObject = ListView_OptionsContent->GetSelectedItem())
	{
		if (UUserWidget* SelectedEntryWidget = ListView_OptionsContent->GetEntryWidgetFromItem(SelectedObject))
		{
			return SelectedEntryWidget;
		}
	}

	return Super::NativeGetDesiredFocusTarget();
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
	if (ResettableDataArray.IsEmpty())
	{
		return;
	}

	UCommonButtonBase* SelectedTabButton = TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabListWidget_OptionsTabs->GetActiveTab());

	const FString SelectedTabButtonName = CastChecked<URswCommonButtonBase>(SelectedTabButton)->GetButtonDisplayText().ToString();

	UFrontendSubsystem::Get(this)->PushConfirmScreenToModalStackAynsc(
		EConfirmScreenType::YesNo,
		FText::FromString(TEXT("Reset")),
		FText::FromString(TEXT("Are you sure you want to reset all the settings under the ") + SelectedTabButtonName + TEXT(" tab?")),
		[this](EConfirmScreenButtonType ClickedButtonType) {
			if (ClickedButtonType != EConfirmScreenButtonType::Confirmed)
			{
				return;
			}

			bIsResettingData = true;
			bool bHasDataFailedToReset = false;

			for (UListDataObject_Base* DataToReset : ResettableDataArray)
			{
				if (!DataToReset)
				{
					continue;
				}

				if (DataToReset->TryResetBackToDefaultValue())
				{
					Debug::Print(DataToReset->GetDataDisplayName().ToString() + TEXT(" was reset"));
				}
				else
				{
					bHasDataFailedToReset = true;
					Debug::Print(DataToReset->GetDataDisplayName().ToString() + TEXT(" failed to reset"));
				}
			}

			if (!bHasDataFailedToReset)
			{
				ResettableDataArray.Empty();
				RemoveActionBinding(ResetActionHandle);
			}

			bIsResettingData = false;
		});
}

void URswWidget_OptionScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void URswWidget_OptionScreen::OnOptionsTabSelected(FName TabId)
{
	DetailsView_ListEntryInfo->ClearDetailsViewInfo();
	TArray<UListDataObject_Base*> FoundListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabId);

	// 这里的listview设置的Items 对应到OnGenerateEntryWidgetInternal里面的Item
	ListView_OptionsContent->SetListItems(FoundListSourceItems);
	ListView_OptionsContent->RequestRefresh();

	if (ListView_OptionsContent->GetNumItems() != 0)
	{
		ListView_OptionsContent->NavigateToIndex(0);
		ListView_OptionsContent->SetSelectedIndex(0);
	}

    	ResettableDataArray.Empty();

	for (UListDataObject_Base* FoundListSourceItem : FoundListSourceItems)
	{
		if (!FoundListSourceItem)
		{
			continue;
		}

		if (!FoundListSourceItem->OnListDataModified.IsBoundToObject(this))
		{
			FoundListSourceItem->OnListDataModified.AddUObject(this, &ThisClass::OnListViewListDataModified);
		}

		if (FoundListSourceItem->CanResetBackToDefaultValue())
		{
			ResettableDataArray.AddUnique(FoundListSourceItem);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
	else
	{
		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
}

void URswWidget_OptionScreen::OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered)
{
	if (!InHoveredItem)
	{
		return;
	}

	UWidget_ListEntry_Base* HoveredEntryWidget = ListView_OptionsContent->GetEntryWidgetFromItem<UWidget_ListEntry_Base>(InHoveredItem);

	check(HoveredEntryWidget);

	HoveredEntryWidget->NativeOnListEntryWidgetHovered(bWasHovered);

	if (bWasHovered)
	{
		DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
			CastChecked<UListDataObject_Base>(InHoveredItem),
			TryGetEntryWidgetClassName(InHoveredItem));
	}
	else
	{
		if (UListDataObject_Base* SelectedItem = ListView_OptionsContent->GetSelectedItem<UListDataObject_Base>())
		{
			DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
				SelectedItem,
				TryGetEntryWidgetClassName(SelectedItem));
		}
	}
}

void URswWidget_OptionScreen::OnListViewItemSelected(UObject* InSelectedItem)
{
	if (!InSelectedItem)
	{
		return;
	}

	DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
		CastChecked<UListDataObject_Base>(InSelectedItem),
		TryGetEntryWidgetClassName(InSelectedItem));
}

FString URswWidget_OptionScreen::TryGetEntryWidgetClassName(UObject* InOwningListItem) const
{
	if (UUserWidget* FoundEntryWidget = ListView_OptionsContent->GetEntryWidgetFromItem(InOwningListItem))
	{
		return FoundEntryWidget->GetClass()->GetName();
	}

	return TEXT("Entry Widget Not Valid");
}

void URswWidget_OptionScreen::OnListViewListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (!ModifiedData || bIsResettingData)
	{
		return;
	}

	if (ModifiedData->CanResetBackToDefaultValue())
	{
		ResettableDataArray.AddUnique(ModifiedData);

		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
	else
	{
		if (ResettableDataArray.Contains(ModifiedData))
		{
			ResettableDataArray.Remove(ModifiedData);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
}
