#pragma once
#include "global.h"

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
	void ExecuteEvent(Event _event);
public:
	void Update();
	void AddEvent(Event _event);
};

