// Zhaobang Liu All Rights Reserved

#include "Widgets/Components/RswCommonRotator.h"

#include "CommonTextBlock.h"

void URswCommonRotator::SetSelectedOptionByText(const FText& InTextOption)
{
	const int32 FoundIndex = TextLabels.IndexOfByPredicate(
		[InTextOption](const FText& TextItem) -> bool {
			return TextItem.EqualTo(InTextOption);
		});

	if (FoundIndex != INDEX_NONE)
	{
		SetSelectedItem(FoundIndex);
	}
	else
	{
		MyText->SetText(InTextOption);
	}
}
