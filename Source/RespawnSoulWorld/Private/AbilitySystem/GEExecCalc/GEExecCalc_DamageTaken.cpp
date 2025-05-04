// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/RswAttributeSet.h"
#include "RswGameplayTags.h"

#include "RswDebugHelper.h"

struct FRswDamageCapture
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

    FRswDamageCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(URswAttributeSet, AttackPower, Source, false)
        DEFINE_ATTRIBUTE_CAPTUREDEF(URswAttributeSet, DefensePower, Target, false)
        DEFINE_ATTRIBUTE_CAPTUREDEF(URswAttributeSet, DamageTaken, Target, false)
    }
};

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

    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    float SourceAttackPower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRswDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
    // Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

    float BaseDamage = 0.f;
    int32 UsedLightAttckComboCount = 0;
    int32 UsedHeavyAttackComboCount = 0;

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
    }

    float TargetDefensePower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRswDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

    //Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

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
