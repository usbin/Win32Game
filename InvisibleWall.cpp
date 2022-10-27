#include "InvisibleWall.h"
#include "SceneManager.h"
#include "Scene_Tool.h"
InvisibleWall::InvisibleWall()
{
}

InvisibleWall::~InvisibleWall()
{
}

void InvisibleWall::Update()
{
	

}

void InvisibleWall::Render(HDC hdc)
{
	//�� �������� ���� ǥ��
	if (dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene())) {
		SelectGdi _(hdc, PEN_TYPE::BLACK_DASH);
		SelectGdi __(hdc, BRUSH_TYPE::HOLLOW);
		Vector2 pos = WorldToRenderPos(get_pos());
		Rectangle(hdc
			, static_cast<int>(pos.x)
			, static_cast<int>(pos.y)
			, static_cast<int>(pos.x + get_scale().x)
			, static_cast<int>(pos.y + get_scale().y));
	}
	ComponentRender(hdc);
	//�� �ܿ� �ƹ��͵� �׸��� ����.
}
