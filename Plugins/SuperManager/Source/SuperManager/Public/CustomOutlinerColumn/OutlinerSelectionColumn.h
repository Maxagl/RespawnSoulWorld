// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ISceneOutlinerColumn.h"

class FOutlinerSelectionLockColumn : public ISceneOutlinerColumn
{
public:
	// 必须加这个ISceneOutliner& SceneOutliner，不然编译不了
	// 原因未知
	FOutlinerSelectionLockColumn(ISceneOutliner& SceneOutliner) {}

	// 这三父类为纯虚函数
	virtual FName GetColumnID() override { return FName("SelectionLock"); }

	static FName GetID() { return FName("SelectionLock"); }

	virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;

	virtual const TSharedRef< SWidget > ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;

private:
	void OnRowWdigetCheckStateChanged(ECheckBoxState NewState, TWeakObjectPtr<AActor> CorrespondingActor);
};