#pragma once
#include "global.h"

class Core;
struct Event {
	EVENT_TYPE type;
	DWORD_PTR param1;
	DWORD_PTR param2;
};


//�̺�Ʈ ���� ó��(������Ʈ ����/����, �� ���� ��)
class EventManager
{
	SINGLETON(EventManager);
private:
	std::vector<Event> events_;
	std::vector<GObject*> dead_objects_;

	//�� ���� �� Exit �� �� ������ ���� ���� �����ӿ� Enter�ϵ��� ��.
	bool change_scene_reserved_ = false;
	SCENE_TYPE reserved_scene_ = SCENE_TYPE::END;
	void ExecuteEvent(Event _event);
public:
	void Update();
	void AddEvent(Event _event);


	friend class Core;
};

