#include "pch.h"
#include "EventManager.h"
#include "SceneManager.h"

EventManager::EventManager() {}

EventManager::~EventManager() {}


void EventManager::Update()
{
	//삭제 작업2: 데드 오브젝트 삭제하기
	SafeDeleteVector<GObject*>(dead_objects_);



	//이벤트 일괄 실행(*이벤트 실행 도중 이벤트 대기열이 찰 수 있으므로 foreach 사용x)
	for (size_t i = 0; i < events_.size(); i++) {
		ExecuteEvent(events_[i]);
	}
	events_.clear();
}

void EventManager::AddEvent(Event _event)
{
	events_.push_back(_event);
}

void EventManager::ExecuteEvent(Event _event)
{
	//이벤트 타입에 따라서
	switch (_event.type) {
	case EVENT_TYPE::CREATE_OBJECT:
	{
		//param1: 오브젝트 포인터
		//param2: 오브젝트 타입
		//생성 작업: 현재 씬에 추가
		SceneManager::GetInstance()->get_current_scene()->AddGObject((GObject*)_event.param1, (GROUP_TYPE)_event.param2);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//param1: 오브젝트 포인터
		//param2: 오브젝트 타입
		//삭제 작업1: 데드 상태로 만들기
		GObject* p_obj = (GObject*)_event.param1;
		p_obj->SetDead();
		dead_objects_.push_back(p_obj);

	}
	break;
	case EVENT_TYPE::CHANGE_SCENE:
	{
		//param1: 다음 씬 타입
		//씬 변경 작업: 다음 씬으로 변경
		SceneManager::GetInstance()->ChangeScene((SCENE_TYPE)_event.param1);

	}
	break;
	}
}
