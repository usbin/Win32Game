#pragma once
#include "global.h"
#include "Ui.h"

class Player;
class TimerUi : public Ui
{
private:
	Player* owner_ = nullptr;
public:
	TimerUi();
	~TimerUi() {};

	void Init(Player* player);

	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
};

