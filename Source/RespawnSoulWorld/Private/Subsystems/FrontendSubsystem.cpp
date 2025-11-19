// Zhaobang Liu All Rights Reserved


#include "Subsystems/FrontendSubsystem.h"

#include "RswDebugHelper.h"

UFrontendSubsystem* UFrontendSubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UFrontendSubsystem>(World->GetGameInstance());
	}

	return nullptr;
}

bool UFrontendSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}

	return false;
}

void UFrontendSubsystem::RegisterCreatedPrimaryLayoutWidget(URswPrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);

	CreatedPrimaryLayout = InCreatedWidget;

	Debug::Print(TEXT("Primary Layout Widget Stored"));
}
