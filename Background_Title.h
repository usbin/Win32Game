#pragma once
#include "global.h"
#include "Ui.h"
class Background_Title : public Ui
{
public:
	Background_Title();
	~Background_Title();
	
private:
public:
	virtual void Update();
	virtual void Render(ID3D11Device* p_d3d_device);
	bool IsAnimationDone();
};

