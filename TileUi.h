#pragma once
#include "global.h"
#include "ButtonUi.h"

class Sprite;
class Director_Scene_Tool;

//�巡�׷� �̵� ����.
//->Tile�� ��ȯ ������ ��� ������ ���� �־�� ��.
//�ܺο��� ������ ���� ����.(��������Ʈ ����, �켱���� ��)
class TileUi : public ButtonUi
{
public:
	TileUi(bool is_static_pos);
	~TileUi();

private:
	Director_Scene_Tool* director_;


public:
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;


	void IncreasePriority();
	void DecreasePriority();

	inline void set_director(Director_Scene_Tool* director) { director_ = director; };
};

