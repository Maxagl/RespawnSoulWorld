// Zhaobang Liu All Rights Reserved


#include "Widgets/RswPrimaryLayout.h"

#include "RswDebugHelper.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UCommonActivatableWidgetContainerBase* URswPrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InTag), TEXT("Can not find the widget stack by the tag %s"), *InTag.ToString());

	return nullptr;
}

void URswPrimaryLayout::RegisterWidgetStack(FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);

			Debug::Print(TEXT("Register widget stack") + InStackTag.ToString());
		}
	}
}
