#pragma once
#include "Res.h"
#include "ResManager.h"

class Texture : public Res
{

private:
	HDC mem_hdc_;
	HBITMAP hbitmap_;
	BITMAP bit_info_;

	Texture();
	virtual ~Texture() override;

public:
	void Load();
	inline UINT get_width() { return bit_info_.bmWidth; };
	inline UINT get_height() { return bit_info_.bmHeight; };
	inline HDC get_hdc() { return mem_hdc_; };
	friend class ResManager;
};

