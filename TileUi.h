#pragma once
#include "global.h"
#include "ButtonUi.h"

class ISprite;
class Director_Scene_Tool;

//드래그로 이동 가능.
//->Tile로 변환 가능한 모든 정보를 갖고 있어야 함.
//외부에서 정보를 변경 가능.(스프라이트 정보, 우선순위 등)
class TileUi : public ButtonUi
{
public:
	TileUi(bool is_static_pos);
	~TileUi();

private:
	Director_Scene_Tool* director_ = nullptr;


public:
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;


	void IncreasePriority();
	void DecreasePriority();

	inline void set_director(Director_Scene_Tool* director) { director_ = director; };
};

