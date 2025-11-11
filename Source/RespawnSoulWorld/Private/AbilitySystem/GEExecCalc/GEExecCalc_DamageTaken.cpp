// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/RswAttributeSet.h"
#include "RswGameplayTags.h"

#include "RswDebugHelper.h"

struct FRswDamageCapture
{
    // 宏干的事情，定义
    // FProperty* AttackPowerProperty
    // FGameplayEffectAttributeCaptureDefinition AttackPowerDef
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

    FRswDamageCapture()
    {
        // 宏干的事情，捕获类里面的属性，带UPROPERTY的。所以这里名称要对上，不然包出错的
        // FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(URswAttributeSet::StaticClass(),GET_MEMBER_NAME_CHECKED(URswAttributeSet,AttackPower)
        // 宏干的事情，
        // FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(AttackPowerProperty, EGameplayEffectAttributeCaptureSource::Source,false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(URswAttributeSet, AttackPower, Source, false)
        DEFINE_ATTRIBUTE_CAPTUREDEF(URswAttributeSet, DefensePower, Target, false)
        DEFINE_ATTRIBUTE_CAPTUREDEF(URswAttributeSet, DamageTaken, Target, false)
    }
};
// 函数局部静态变量单例模式
static const FRswDamageCapture& GetRswDamageCapture()
{
    static FRswDamageCapture RswDamageCapture;
    return RswDamageCapture;
}


UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
    /*Slow way of doing capture*/
    //FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
    //	URswAttributeSet::StaticClass(),
    //	GET_MEMBER_NAME_CHECKED(URswAttributeSet,AttackPower)
    //);

    //FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
    //	AttackPowerProperty,
    //	EGameplayEffectAttributeCaptureSource::Source,
    //	false
    //);

    //RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

    RelevantAttributesToCapture.Add(GetRswDamageCapture().AttackPowerDef);
    RelevantAttributesToCapture.Add(GetRswDamageCapture().DefensePowerDef);
    RelevantAttributesToCapture.Add(GetRswDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

    /*EffectSpec.GetContext().GetSourceObject();
    EffectSpec.GetContext().GetAbility();
    EffectSpec.GetContext().GetInstigator();
    EffectSpec.GetContext().GetEffectCauser();*/

    // 这里两个tag返回空
    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    float SourceAttackPower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRswDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
    // Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

    float BaseDamage = 0.f;
    int32 UsedLightAttckComboCount = 0;
    int32 UsedHeavyAttackComboCount = 0;

    int wind = 1;
    float windBuff = 0.f;

    for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
    {
        if (TagMagnitude.Key.MatchesTagExact(RswGameplayTags::Shared_SetByCaller_BaseDamage))
        {
            BaseDamage = TagMagnitude.Value;
            //Debug::Print(TEXT("BaseDamage"), BaseDamage);
        }

        if (TagMagnitude.Key.MatchesTagExact(RswGameplayTags::Player_SetByCaller_AttackType_Light))
        {
            UsedLightAttckComboCount = TagMagnitude.Value;
            //Debug::Print(TEXT("UsedLightAttckComboCount"), UsedLightAttckComboCount);
        }

        if (TagMagnitude.Key.MatchesTagExact(RswGameplayTags::Player_SetByCaller_AttackType_Heavy))
        {
            UsedHeavyAttackComboCount = TagMagnitude.Value;
            //Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
        }
        if (TagMagnitude.Key.MatchesTagExact(RswGameplayTags::Shared_SetByCaller_Buff_WindMastery))
        {
            windBuff = TagMagnitude.Value;
            //Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
        }
        if (TagMagnitude.Key.MatchesTagExact(RswGameplayTags::Player_SetByCaller_AttackType_Magic_Wind))
        {
            wind = TagMagnitude.Value;
        }
    }

    float TargetDefensePower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRswDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

    //Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);
    if (wind == 0)
    {
        if (UsedLightAttckComboCount != 0)
        {
            const float DamageIncreasePercentLight = (UsedLightAttckComboCount - 1) * 0.05 + 1.f;

            BaseDamage *= DamageIncreasePercentLight;
            //Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
        }

        if (UsedHeavyAttackComboCount != 0)
        {
            const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;

            BaseDamage *= DamageIncreasePercentHeavy;
            //Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);
        }

        const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
        // Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

        if (FinalDamageDone > 0.f)
        {
            OutExecutionOutput.AddOutputModifier(
                FGameplayModifierEvaluatedData(
                    GetRswDamageCapture().DamageTakenProperty,
                    EGameplayModOp::Override,
                    FinalDamageDone
                )
            );
        }
    }
    else if(wind == 1)
    {

        BaseDamage *= (windBuff + 1.f);
        const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
        Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);
        if (FinalDamageDone > 0.f)
        {
            OutExecutionOutput.AddOutputModifier(
                FGameplayModifierEvaluatedData(
                    GetRswDamageCapture().DamageTakenProperty,
                    EGameplayModOp::Override,
                    FinalDamageDone
                )
            );
        }
    }

}
