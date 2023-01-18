#include "Decorator.h"

Decorator::Decorator() {};
Decorator::~Decorator() {
	delete simple_frame_;
	delete horizontal_split_frame_;
	delete inventory_cell_frame_;
	delete console_frame_;
};

SimpleFrame* Decorator::GetSimpleFrame()
{
	if (!simple_frame_) {
		simple_frame_ = DEBUG_NEW SimpleFrame();
	}

	return simple_frame_;
}

HorizontalSplitFrame* Decorator::GetHorizontalSplitFrame()
{
	if (!horizontal_split_frame_) {
		horizontal_split_frame_ = DEBUG_NEW HorizontalSplitFrame();
	}
	return horizontal_split_frame_;
}

InventoryCellFrame* Decorator::GetInventoryCellFrame()
{
	if (!inventory_cell_frame_) {
		inventory_cell_frame_ = DEBUG_NEW InventoryCellFrame();
	}
	return inventory_cell_frame_;
}

ConsoleFrame* Decorator::GetConsoleFrame()
{
	if (!console_frame_) {
		console_frame_ = DEBUG_NEW ConsoleFrame();
	}
	return console_frame_;
}
