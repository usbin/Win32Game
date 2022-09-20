#include "pch.h"
#include "SelectGDI.h"
#include "Core.h"

SelectGdi::SelectGdi(HDC hdc, PEN_TYPE pen_type) 
	:default_pen_()
	,default_brush_(){
	hdc_ = hdc;
	default_pen_ = (HPEN)SelectObject(hdc, Core::GetInstance()->GetPen(pen_type));
}
SelectGdi::SelectGdi(HDC hdc, BRUSH_TYPE brush_type)
	: default_pen_()
	, default_brush_() {
	hdc_ = hdc;
	default_brush_ = (HBRUSH)SelectObject(hdc, Core::GetInstance()->GetBrush(brush_type));
}


SelectGdi::~SelectGdi() {
	SelectObject(hdc_, default_pen_);
	SelectObject(hdc_, default_brush_);

}