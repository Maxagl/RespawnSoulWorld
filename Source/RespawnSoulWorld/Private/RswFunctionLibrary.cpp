// Fill out your copyright notice in the Description page of Project Settings.


#include "RswFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "RswGameplayTags.h"
#include "GenericTeamAgentInterface.h"
#include "RswTypes/RswCountDownAction.h"

#include "RswDebugHelper.h"

URswAbilitySystemComponent* URswFunctionLibrary::NativeGetRswASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<URswAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void URswFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	URswAbilitySystemComponent* ASC = NativeGetRswASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void URswFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	URswAbilitySystemComponent* ASC = NativeGetRswASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool URswFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	URswAbilitySystemComponent* ASC = NativeGetRswASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void URswFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ERswConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ERswConfirmType::Yes : ERswConfirmType::No;
}

UPawnCombatComponent* URswFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* URswFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, ERswValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? ERswValidType::Valid : ERswValidType::Invalid;

	return CombatComponent;
}

bool URswFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float URswFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag URswFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return RswGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return RswGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -135.f || OutAngleDifference>135.f)
	{
		return RswGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return RswGameplayTags::Shared_Status_HitReact_Right;
	}

	return RswGameplayTags::Shared_Status_HitReact_Front;
}

bool URswFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	//const FString DebugString = FString::Printf(TEXT("Dot Result: %f %s"), DotResult, DotResult < -0.1f ? TEXT("Valid Block") : TEXT("InvalidBlock"));

	//Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);

	return DotResult < -0.1f;
}

bool URswFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	URswAbilitySystemComponent* SourceASC = NativeGetRswASCFromActor(InInstigator);
	URswAbilitySystemComponent* TargetASC = NativeGetRswASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void URswFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
	float& OutRemainingTime, ERswCountDownActionInput CountDownInput,
	UPARAM(DisplayName = "Output") ERswCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;

	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if (!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FRswCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FRswCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownInput == ERswCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FRswCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo)
			);
		}
	}

	if (CountDownInput == ERswCountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}
