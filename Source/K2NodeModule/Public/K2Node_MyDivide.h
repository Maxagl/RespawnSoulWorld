// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_MyDivide.generated.h"

/**
 * 
 */
UCLASS()
class K2NODEMODULE_API UK2Node_MyDivide : public UK2Node
{
	GENERATED_BODY()
    // Overrided from UEdGraphNode.
    virtual void AllocateDefaultPins() override;
    virtual FText GetTooltipText() const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

    // Overrided from UK2Node.
    virtual bool IsNodePure() const override;
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetMenuCategory() const override;
    void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
};
