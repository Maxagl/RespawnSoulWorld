// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_RingOfGust.h"
#include "RswFunctionLibrary.h"
#include "Characters/RswHeroCharacter.h"
#include "AbilitySystem/RswAbilitySystemComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "RswGameplayTags.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "RswDebugHelper.h"

void UHeroGameplayAbility_RingOfGust::OnInputPressed()
{
    ChargeTime = 0;
    bIsCharging = true;
    
    GetWorld()->GetTimerManager().SetTimer(
        ChargeTimeHandle,
        this,
        &ThisClass::TickCharge,
        0.01f,
        true
    );
    GetHeroCharacterFromActorInfo()->GetHeroUIComponent()->OnDisplayChargeBar.Broadcast(true);
    Debug::Print(FString("Start Charging"));
}

void UHeroGameplayAbility_RingOfGust::OnInputReleased()
{
    if (!bIsCharging) return;

    bIsCharging = false;

    GetWorld()->GetTimerManager().ClearTimer(ChargeTimeHandle);
    if (!ReleaseTag.IsValid())
    {
        Debug::Print(FString("Should Set ReleaseTag In GA"));
    }
    URswFunctionLibrary::AddGameplayTagToActorIfNone(Cast<AActor>(GetHeroCharacterFromActorInfo()), ReleaseTag);
    FTimerHandle Handle;
    GetWorld()->GetTimerManager().SetTimer(Handle, [this]{URswFunctionLibrary::RemoveGameplayTagFromActorIfFound(Cast<AActor>(GetHeroCharacterFromActorInfo()), ReleaseTag);}, 0.3f, false);

    // 根据蓄力时间执行攻击（可用于动画、粒子、伤害等）
    Debug::Print(FString("Release"));
    ExecuteChargedAttack(ChargeTime);
    GetHeroCharacterFromActorInfo()->GetHeroUIComponent()->OnDisplayChargeBar.Broadcast(false);
    if (ChargeTime < ChargeConfig.MaxChargeTime)
    {
        Debug::Print(FString("ChargeTime: ") + FString::SanitizeFloat(ChargeTime));
        OnMaxCharge.Broadcast();
    }
}

void UHeroGameplayAbility_RingOfGust::TickCharge()
{
    if (!bIsCharging) return;

    ChargeTime += 0.01f;
    //Debug::Print(FString::SanitizeFloat(ChargeTime));
    GetHeroCharacterFromActorInfo()->GetHeroUIComponent()->OnChargeTimeChanged.Broadcast(ChargeTime / ChargeConfig.MaxChargeTime);
    if (ChargeTime > 1.0f)
    {
        USkeletalMeshComponent* SkeletalMesh = GetHeroCharacterFromActorInfo()->GetMesh();
        FName SocketName = TEXT("ChargeSocket");
        FVector Location = SkeletalMesh->GetSocketLocation(SocketName);
        FRotator Rotation = SkeletalMesh->GetSocketRotation(SocketName);
        UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            NiagaraSystem,
            Location,
            Rotation,
            FVector(1.0f), // 缩放
            true,          // 自动销毁
            true,          // 自动激活
            ENCPoolMethod::AutoRelease,
            true           // 预取
        );
        if (NiagaraComp)
        {
            NiagaraComp->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepWorldTransform, SocketName);
        }
    }
    if (ChargeTime >= ChargeConfig.MaxChargeTime)
    {
        ChargeTime = ChargeConfig.MaxChargeTime;
        OnMaxCharge.Broadcast();
    }
}

bool UHeroGameplayAbility_RingOfGust::CheckCoolDown() const
{
    return GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(CooldownTag);
}

void UHeroGameplayAbility_RingOfGust::ApplyCoolDown(float CoolDownTime)
{
    FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(GE_Cooldown_RingGust, GetAbilityLevel());
    SpecHandle.Data->SetSetByCallerMagnitude(CooldownDurationTag, CoolDownTime);
    ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);
}

