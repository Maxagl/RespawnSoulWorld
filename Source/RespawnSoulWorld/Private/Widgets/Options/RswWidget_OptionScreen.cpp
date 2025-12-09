// Zhaobang Liu All Rights Reserved

#include "Widgets/Options/RswWidget_OptionScreen.h"

#include "ICommonInputModule.h"
#include "Input/CommonUIInputTypes.h"

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
}

void URswWidget_OptionScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered"));
}

void URswWidget_OptionScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}
