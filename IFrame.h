#pragma once
#include "global.h"
#include "Ui.h"


class IFrame
{
public:
	virtual void Render(ID3D11Device* p_d3d_device, Ui* ui, RENDER_LAYER layer) = 0;
};

