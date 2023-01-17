#pragma once
#include "global.h"
#include "IFrame.h"
class SimpleFrame : public IFrame
{
public:
	// IFrame을(를) 통해 상속됨
	virtual void Render(ID3D11Device* p_d3d_device, Ui* ui, RENDER_LAYER layer) override;
};

