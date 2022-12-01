#include "ImageUi.h"
#include "Texture.h"

ImageUi::ImageUi(bool is_static_pos)
	: Ui(is_static_pos)
{
}

ImageUi::~ImageUi()
{
}

void ImageUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);


	ChildrenRender(p_d3d_device);
}
