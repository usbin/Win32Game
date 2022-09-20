#pragma once
#include <set>
#include "GObject.h"

#define FPS 60
class Core {
	SINGLETON(Core);

private:
	POINT pt_resolution_;
	HWND hwnd_;
	HDC hdc_;
	HDC hdc_mem_;
	HBITMAP hbitmap_;
	HPEN pens[static_cast<int>(PEN_TYPE::END)];
	HBRUSH brushes[static_cast<int>(BRUSH_TYPE::END)];
	
	void SyncResolution();
	void InitPenAndBrush();
public:
	int Init(HWND hwnd, int width, int height);
	int OnDestroy();
	bool Progress();
	inline HDC get_main_hdc() { return hdc_; };
	inline POINT get_pt_resolution() { return pt_resolution_; };

	inline HPEN GetPen(PEN_TYPE pen_type) {
		return pens[static_cast<int>(pen_type)];
	};
	inline HBRUSH GetBrush(BRUSH_TYPE brush_type) {
		return brushes[static_cast<int>(brush_type)];
	}
};
