#pragma once
#include "Ui.h"
class Texture;

class ImageUi : public Ui
{
public:
	ImageUi(bool is_static_pos);
	virtual ~ImageUi();

	virtual void Render(LPDIRECT3DDEVICE9 p_d3d_device) override;
};

