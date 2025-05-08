// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/RswHeroController.h"

ARswHeroController::ARswHeroController()
{
    HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId ARswHeroController::GetGenericTeamId() const
{
    return HeroTeamID;
}
