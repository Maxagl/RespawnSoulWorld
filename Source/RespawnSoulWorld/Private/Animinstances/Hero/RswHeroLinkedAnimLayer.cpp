// Fill out your copyright notice in the Description page of Project Settings.


#include "Animinstances/Hero/RswHeroLinkedAnimLayer.h"
#include "AnimInstances/Hero/RswHeroAnimInstance.h"

URswHeroAnimInstance* URswHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
    return Cast<URswHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
