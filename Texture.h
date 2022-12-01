#pragma once
#include "Res.h"
#include "ResManager.h"

class Texture : public Res
{

private:

	//DX11 »ç¿ë
	ID3D11ShaderResourceView* p_resource_view_;
	D3D11_TEXTURE2D_DESC texture_desc_;

	Texture();
	virtual ~Texture() override;

public:
	void Load();
	inline UINT get_width() { return texture_desc_.Width; };
	inline UINT get_height() { return texture_desc_.Height; };
	inline const Vector2& get_size() { return Vector2{ get_width(), get_height() }; };
	inline ID3D11ShaderResourceView* get_resource_view() { return p_resource_view_; };
	friend class ResManager;

};

