#pragma once
#include "global.h"
#include <set>
#include "GObject.h"

#define FPS 60
class Core {
	SINGLETON(Core);

private:
	POINT pt_resolution_;
	HWND hwnd_ = 0;
	HINSTANCE hinst_ = 0;
	HDC hdc_ = 0;
	HDC hdc_mem_ = 0;
	HBITMAP hbitmap_ = 0;
	HPEN pens[static_cast<int>(PEN_TYPE::END)] = {0};
	HBRUSH brushes[static_cast<int>(BRUSH_TYPE::END)] = {0};


	void InitPenAndBrush();
public:
	int Init(HWND hwnd, HINSTANCE hInst, int width, int height);
	int OnDestroy();
	bool Progress();
	inline HDC get_main_hdc() { return hdc_; };
	inline HWND get_main_hwnd() { return hwnd_; };
	inline POINT get_pt_resolution() { return pt_resolution_; };
	inline Vector2 get_resolution() { return Vector2{ pt_resolution_ }; };
	inline HINSTANCE get_instance() { return hinst_; };

	inline HPEN GetPen(PEN_TYPE pen_type) {
		return pens[static_cast<int>(pen_type)];
	};
	inline HBRUSH GetBrush(BRUSH_TYPE brush_type) {
		return brushes[static_cast<int>(brush_type)];
	}

	void SyncResolution();
};
