#pragma once
#include "global.h"
#include "ISavable.h"
class GObject;
class Sprite;
class RealObjectRenderComponent : public ISavable
{
public:
	RealObjectRenderComponent(GObject* owner) {};
	virtual ~RealObjectRenderComponent() { delete sprite_; };

private:
	Sprite* sprite_;

public:
	virtual void Update(GObject* owner){};
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device);

	virtual Sprite* get_sprite() { return sprite_; };
	virtual void ChangeSprite(Sprite* sprite);

	// ISavable을(를) 통해 상속됨
	virtual void SaveToFile(FILE* p_file) override;
	virtual void LoadFromFile(FILE* p_file) override;
};

