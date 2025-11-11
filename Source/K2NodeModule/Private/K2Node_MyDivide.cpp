// Fill out your copyright notice in the Description page of Project Settings.


#include "K2Node_MyDivide.h"

#include "KismetCompiler.h"
#include "K2Node_CallFunction.h"
#include "EditorCategoryUtils.h"
#include "BlueprintNodeSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Internationalization/Text.h"
#include "BlueprintActionDatabaseRegistrar.h"

FText UK2Node_MyDivide::GetTooltipText() const
{
    // Returns text to be displayed in Tooltip.
    return FText::FromString("MyDivideGet quotient and remainder from dividing two integer");
}

FText UK2Node_MyDivide::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    // Returns text to be displayed in the title section.
    return FText::FromString("MyDivide");
}

bool UK2Node_MyDivide::IsNodePure() const
{
    return true;
}

void UK2Node_MyDivide::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    UClass* ActionKey = GetClass();
    if (ActionRegistrar.IsOpenForRegistration(ActionKey))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
        check(NodeSpawner != nullptr);

        ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
    }
}

FText UK2Node_MyDivide::GetMenuCategory() const
{
    // Register the category "Math".
    return FEditorCategoryUtils::GetCommonCategory(FCommonEditorCategory::Math);
}

namespace
{
    static const FName APinName(TEXT("A"));
    static const FName BPinName(TEXT("B"));
    static const FName QuotientPinName(TEXT("Quotient"));
    static const FName RemainderPinName(TEXT("Remainder"));
}

void UK2Node_MyDivide::AllocateDefaultPins()
{
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, APinName);
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, BPinName);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Int, QuotientPinName);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Int, RemainderPinName);
}

void UK2Node_MyDivide::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    // This equals to the placement of "/" node.
    UK2Node_CallFunction* CallDivideFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    CallDivideFunction->SetFromFunction(UKismetMathLibrary::StaticClass()->FindFunctionByName(GET_MEMBER_NAME_CHECKED(UKismetMathLibrary, Divide_IntInt)));
    CallDivideFunction->AllocateDefaultPins();
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(QuotientPinName), *CallDivideFunction->GetReturnValuePin());
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(APinName), *CallDivideFunction->FindPinChecked(TEXT("A")));
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(BPinName), *CallDivideFunction->FindPinChecked(TEXT("B")));

    // This equals to the placement of "%" node.
    UK2Node_CallFunction* CallPercentFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    CallPercentFunction->SetFromFunction(UKismetMathLibrary::StaticClass()->FindFunctionByName(GET_MEMBER_NAME_CHECKED(UKismetMathLibrary, Percent_IntInt)));
    CallPercentFunction->AllocateDefaultPins();
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(RemainderPinName), *CallPercentFunction->GetReturnValuePin());
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(APinName), *CallPercentFunction->FindPinChecked(TEXT("A")));
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(BPinName), *CallPercentFunction->FindPinChecked(TEXT("B")));
}