#pragma once
class SelectGdi
{
private:
	HPEN default_pen_ = 0;
	HBRUSH default_brush_ = 0;
	HDC hdc_ = 0;
public:
	SelectGdi(HDC hdc, PEN_TYPE pen_type);
	SelectGdi(HDC hdc, BRUSH_TYPE brush_type);
	~SelectGdi();
};

