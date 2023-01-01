#pragma once
#include "global.h"
#include "RealObjectRenderComponent.h"
class RealObject;
class PlayerRenderComponent : public RealObjectRenderComponent
{
public:
	PlayerRenderComponent(GObject* owner);
	~PlayerRenderComponent();

private:
	Sprite* sprites[(int)DIRECTION::END][(int)PLAYER_STATE::END];

public:
	virtual void Update(GObject* owner);
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device);

	virtual void SaveToFile(FILE* p_file) override;
	virtual void LoadFromFile(FILE* p_file) override;
};

