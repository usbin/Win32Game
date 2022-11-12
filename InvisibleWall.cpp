#include "InvisibleWall.h"
#include "SceneManager.h"
#include "Scene_Tool.h"
#include "Collider.h"
InvisibleWall::InvisibleWall()
{
}

InvisibleWall::~InvisibleWall()
{
}

void InvisibleWall::Update()
{
	get_collider()->set_scale(get_scale());
}

void InvisibleWall::Render(LPDIRECT3DDEVICE9 p_d3d_device)
{
	//툴 씬에서만 점선 표시
	if (dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene())) {
		Vector2 pos = WorldToRenderPos(get_pos());
		
		//SelectGdi _(hdc, PEN_TYPE::BLACK_DASH);
		//SelectGdi __(hdc, BRUSH_TYPE::HOLLOW);
		/*Rectangle(hdc
			, static_cast<int>(pos.x - get_scale().x/2.f)
			, static_cast<int>(pos.y - get_scale().y/2.f)
			, static_cast<int>(pos.x + get_scale().x/2.f)
			, static_cast<int>(pos.y + get_scale().y/2.f));*/
	}
	ComponentRender(p_d3d_device);
	//그 외엔 아무것도 그리지 않음.
}
