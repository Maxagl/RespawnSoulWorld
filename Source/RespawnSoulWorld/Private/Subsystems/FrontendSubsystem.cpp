// Zhaobang Liu All Rights Reserved

#include "Subsystems/FrontendSubsystem.h"

#include "RswDebugHelper.h"
#include "RswGameplayTags.h"
#include "Engine/AssetManager.h"
#include "FrontendFunctionLibrary.h"
#include "Widgets/RswPrimaryLayout.h"
#include "Widgets/RswWidget_ConfirmScreen.h"
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

void UFrontendSubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<URswActivatableWidgetBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, URswActivatableWidgetBase*)> AysncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(InSoftWidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([InSoftWidgetClass, this, InWidgetStackTag, AysncPushStateCallback]() {
		UClass* LoadedWidgetClass = InSoftWidgetClass.Get();

		check(LoadedWidgetClass && CreatedPrimaryLayout);

		UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);

        // 所有的异步最后都回到了这个UCommonActivatableWidgetContainerBase 的 AddWidget 这个函数
		URswActivatableWidgetBase* CreatedWidget = FoundWidgetStack->AddWidget<URswActivatableWidgetBase>(
			LoadedWidgetClass, [AysncPushStateCallback](URswActivatableWidgetBase& CreatedWidgetInstance) {
				AysncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
			});

		AysncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
	}));
}

void UFrontendSubsystem::PushConfirmScreenToModalStackAynsc(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreatedInfoObject = nullptr;

	switch (InScreenType)
	{
		case EConfirmScreenType::Ok:
			CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle, InScreenMsg);
			break;

		case EConfirmScreenType::YesNo:
			CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMsg);
			break;

		case EConfirmScreenType::OKCancel:
			CreatedInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle, InScreenMsg);
			break;

		case EConfirmScreenType::Unknown:
			break;

		default:
			break;
	}

	check(CreatedInfoObject);

	PushSoftWidgetToStackAsync(
		RswGameplayTags::Frontend_WidgetStack_Modal,
		UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(RswGameplayTags::Frontend_Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, URswActivatableWidgetBase* PushedWidget) {
			if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				URswWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<URswWidget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		});
}
