#pragma once
#include "global.h"
#include "Ui.h"

class Sprite;
class Director_Scene_Tool;

//�巡�׷� �̵� ����.
//->Tile�� ��ȯ ������ ��� ������ ���� �־�� ��.
//�ܺο��� ������ ���� ����.(��������Ʈ ����, �켱���� ��)
class TileUi : public Ui
{
public:
	TileUi(bool is_static_pos);
	~TileUi();

private:
	Director_Scene_Tool* director_;
	bool is_dragging_;
	Vector2 prev_drag_pos_;
	Vector2 drag_preview_pos_;

	bool is_picked_;//���콺�� ���� �����ΰ�

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void LbuttonClick() override;
	virtual void LbuttonDown() override;
	virtual void LbuttonUp() override;

	void IncreasePriority();
	void DecreasePriority();

	inline void set_director(Director_Scene_Tool* director) { director_ = director; };
	inline void Pick() { is_picked_ = true; };
	inline void Unpick() { is_picked_ = false; };
};

