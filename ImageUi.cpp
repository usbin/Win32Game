#include "ImageUi.h"
#include "Texture.h"

ImageUi::ImageUi(bool is_static_pos)
	: Ui(is_static_pos)
{
}

ImageUi::~ImageUi()
{
}

void ImageUi::Render(HDC hdc)
{
	Ui::Render(hdc);


	ChildrenRender(hdc);
}
