#pragma once
#include "global.h"
#include "IFrame.h"
class SimpleFrame : public IFrame
{
public:
	// IFrame��(��) ���� ��ӵ�
	virtual void Render(ID3D11Device* p_d3d_device, Ui* ui, RENDER_LAYER layer) override;
};

