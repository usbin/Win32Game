#include "Texture.h"
#include "PathManager.h"
#include "Core.h"
#include "DXClass.h"
Texture::Texture(){
}

Texture::~Texture()
{
}
void Texture::Load()
{
	tstring texture_path = PathManager::GetInstance()->GetContentPath() + get_relative_path();



	if (FAILED(D3DX11CreateShaderResourceViewFromFile(DXClass::GetInstance()->get_d3d_device(), texture_path.c_str(), NULL, NULL, &p_resource_view_, NULL))) {
		return;
	}


	ID3D11Texture2D* p_texture_interface;
	ID3D11Resource* res;
	p_resource_view_->GetResource(&res);
	res->QueryInterface<ID3D11Texture2D>(&p_texture_interface);
	p_texture_interface->GetDesc(&texture_desc_);

	res->Release();

}
