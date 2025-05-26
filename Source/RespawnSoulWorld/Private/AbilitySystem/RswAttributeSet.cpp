// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RswAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "RswFunctionLibrary.h"
#include "RswGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/HeroUIComponent.h"

#include "RswDebugHelper.h"
URswAttributeSet::URswAttributeSet()
{
    InitCurrentHealth(1.f);
    InitMaxHealth(1.f);
    InitCurrentRage(1.f);
    InitMaxRage(1.f);
    InitAttackPower(1.f);
    InitDefensePower(1.f);
}

// PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data) only triggers after changes to the BaseValue of an Attribute from an instant GameplayEffect.
// 注意后面这几个条件，要改变basevalue， 同时钥匙instant gameplayeffect.
void URswAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

    if (!CachedPawnUIInterface.IsValid())
    {
        CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
    }
    checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

    UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

    checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

    if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
    {
        const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

        SetCurrentHealth(NewCurrentHealth);
        PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
    }

    if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
    {
        const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());

        SetCurrentRage(NewCurrentRage);

        if (GetCurrentRage() == GetMaxRage())
        {
            URswFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), RswGameplayTags::Player_Status_Rage_Full);
        }
        else if (GetCurrentRage() == 0.f)
        {
            URswFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), RswGameplayTags::Player_Status_Rage_None);
        }
        else
        {
            URswFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), RswGameplayTags::Player_Status_Rage_Full);
            URswFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), RswGameplayTags::Player_Status_Rage_None);
        }

        if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
        {
            HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
        }
    }

    if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
    {
        const float OldHealth = GetCurrentHealth();
        const float DamageDone = GetDamageTaken();

        const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

        SetCurrentHealth(NewCurrentHealth);

        const FString DebugString = FString::Printf(
            TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"),
            OldHealth,
            DamageDone,
            NewCurrentHealth
        );

        Debug::Print(DebugString, FColor::Green);

        //TODO::Notify the UI 
        PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

        //TODO::Handle character death
        if (GetCurrentHealth() == 0.f)
        {
            URswFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), RswGameplayTags::Shared_Status_Dead);
        }
    }
}
