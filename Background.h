#pragma once
#include "global.h"
#include "RealObject.h"


#define BACKGROUND_RATIO_X 2
#define BACKGROUND_RATIO_Y 2

class Background : public RealObject
{
public:
	Background();
	~Background();
private:
public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

