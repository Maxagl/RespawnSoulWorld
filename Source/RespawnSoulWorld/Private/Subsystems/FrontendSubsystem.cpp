// Zhaobang Liu All Rights Reserved

#include "Subsystems/FrontendSubsystem.h"

#include "RswDebugHelper.h"
#include "Engine/AssetManager.h"
#include "Widgets/RswPrimaryLayout.h"
#include "Widgets/RswActivatableWidgetBase.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

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

void UFrontendSubsystem::PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<URswActivatableWidgetBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, URswActivatableWidgetBase*)> AysncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(InSoftWidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([InSoftWidgetClass, this, InWidgetStackTag, AysncPushStateCallback]() {
		UClass* LoadedWidgetClass = InSoftWidgetClass.Get();

		check(LoadedWidgetClass && CreatedPrimaryLayout);

		UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);

		URswActivatableWidgetBase* CreatedWidget = FoundWidgetStack->AddWidget<URswActivatableWidgetBase>(
			LoadedWidgetClass, [AysncPushStateCallback](URswActivatableWidgetBase& CreatedWidgetInstance) {
				AysncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
			});

		AysncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
	}));
}
