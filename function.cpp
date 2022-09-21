#include "function.h"
#include "GObject.h"
#include "EventManager.h"
#include "Time.h"
#include "Camera.h"

void CreateGObject(GObject* object, GROUP_TYPE type) {
	Event eve = {};
	eve.type = EVENT_TYPE::CREATE_OBJECT;
	eve.param1 = (DWORD_PTR)object;
	eve.param2 = (DWORD_PTR)type;

	EventManager::GetInstance()->AddEvent(eve);
}

void DeleteGObject(GObject* object, GROUP_TYPE type) {
	Event eve = {};
	eve.type = EVENT_TYPE::DELETE_OBJECT;
	eve.param1 = (DWORD_PTR)object;
	eve.param2 = (DWORD_PTR)type;

	EventManager::GetInstance()->AddEvent(eve);
}

void ChangeScene(SCENE_TYPE scene_type)
{
	Event eve = {};
	eve.type = EVENT_TYPE::CHANGE_SCENE;
	eve.param1 = (DWORD_PTR)scene_type;

	EventManager::GetInstance()->AddEvent(eve);
}

float DtF()
{
	return static_cast<float>(Time::GetInstance()->dt_f());

}

Vector2 GetRenderPos(Vector2 world_pos)
{
	return Camera::GetInstance()->GetRenderPos(world_pos);
}

Vector2 GetWorldPos(Vector2 render_pos)
{
	return Camera::GetInstance()->GetWorldPos(render_pos);
}


