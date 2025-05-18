// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class URswWidgetBase;
/**
 * 
 */
UCLASS()
class RESPAWNSOULWORLD_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(URswWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<URswWidgetBase*> EnemyDrawnWidgets;
};
