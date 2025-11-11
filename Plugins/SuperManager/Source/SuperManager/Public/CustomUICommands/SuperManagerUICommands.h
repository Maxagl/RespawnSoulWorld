// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Framework/Commands/Commands.h"


// 这个是 Curiously Recurring Template Pattern（CRTP），中文常译为“奇异递归模板模式”。
class FSuperManagerUICommands : public TCommands<FSuperManagerUICommands>
{
public:
	FSuperManagerUICommands() : TCommands<FSuperManagerUICommands>(
		TEXT("SuperManager"),
		FText::FromString(TEXT("Super Manager UI Commands")),
		NAME_None,
		TEXT("SuperManager")
	) {}

	virtual void RegisterCommands() override;
	TSharedPtr<FUICommandInfo> LockActorSelection;
	TSharedPtr<FUICommandInfo> UnlockActorSelection;
};
