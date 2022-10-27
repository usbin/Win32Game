#pragma once
#include "Ui.h"
class Texture;

class ImageUi : public Ui
{
public:
	ImageUi(bool is_static_pos);
	virtual ~ImageUi();

	virtual void Render(HDC hdc) override;
};

