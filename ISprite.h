#pragma once
#include "global.h"
class Texture;
class GObject;
/// <summary>
/// GObject가 포인터로 갖고 있는 이미지 정보.
/// </summary>
class ISprite
{
public:
	virtual ~ISprite() = 0 {};

private:



public:
	virtual void Render(ID3D11Device* p_d3d_device) = 0;

	inline virtual void set_texture(Texture* texture) = 0;
	inline virtual Texture* get_texture() = 0;
	inline virtual void set_base_pos(Vector2 pos) = 0;
	inline virtual Vector2 get_base_pos() = 0;
	inline virtual void set_scale(Vector2 scale) = 0;
	inline virtual Vector2 get_scale() = 0;



};

