#pragma once
class SelectGdi
{
private:
	HPEN default_pen_;
	HBRUSH default_brush_;
	HDC hdc_;
public:
	SelectGdi(HDC hdc, PEN_TYPE pen_type);
	SelectGdi(HDC hdc, BRUSH_TYPE brush_type);
	~SelectGdi();
};

