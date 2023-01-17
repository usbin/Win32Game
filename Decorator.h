#pragma once
#include "global.h"
#include "SimpleFrame.h"
#include "HorizontalSplitFrame.h"
#include "InventoryCellFrame.h"
class Ui;
/// <summary>
/// render(Ui)�� ȣ���ϸ� Ui�� �ٸ��ִ� Ŭ����
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

