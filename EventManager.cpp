#include "pch.h"
#include "EventManager.h"
#include "SceneManager.h"

EventManager::EventManager() {}

EventManager::~EventManager() {}


void EventManager::Update()
{
	//���� �۾�2: ���� ������Ʈ �����ϱ�
	SafeDeleteVector<GObject*>(dead_objects_);



	//�̺�Ʈ �ϰ� ����(*�̺�Ʈ ���� ���� �̺�Ʈ ��⿭�� �� �� �����Ƿ� foreach ���x)
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
	//�̺�Ʈ Ÿ�Կ� ����
	switch (_event.type) {
	case EVENT_TYPE::CREATE_OBJECT:
	{
		//param1: ������Ʈ ������
		//param2: ������Ʈ Ÿ��
		//���� �۾�: ���� ���� �߰�
		SceneManager::GetInstance()->get_current_scene()->AddGObject((GObject*)_event.param1, (GROUP_TYPE)_event.param2);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//param1: ������Ʈ ������
		//param2: ������Ʈ Ÿ��
		//���� �۾�1: ���� ���·� �����
		GObject* p_obj = (GObject*)_event.param1;
		p_obj->SetDead();
		dead_objects_.push_back(p_obj);

	}
	break;
	case EVENT_TYPE::CHANGE_SCENE:
	{
		//param1: ���� �� Ÿ��
		//�� ���� �۾�: ���� ������ ����
		SceneManager::GetInstance()->ChangeScene((SCENE_TYPE)_event.param1);

	}
	break;
	}
}
