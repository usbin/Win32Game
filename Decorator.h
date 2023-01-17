#pragma once
#include "global.h"
#include "SimpleFrame.h"
#include "HorizontalSplitFrame.h"
#include "InventoryCellFrame.h"
class Ui;
/// <summary>
/// render(Ui)를 호출하면 Ui를 꾸며주는 클래스
/// </summary>
class Decorator
{
public:
	SINGLETON(Decorator);
	SimpleFrame* simple_frame_ = nullptr;
	HorizontalSplitFrame* horizontal_split_frame_ = nullptr;
	InventoryCellFrame* inventory_cell_frame_ = nullptr;

public:
	SimpleFrame* GetSimpleFrame();
	HorizontalSplitFrame* GetHorizontalSplitFrame();
	InventoryCellFrame* GetInventoryCellFrame();
};

