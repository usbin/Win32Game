#pragma once
#include "global.h"

struct Event {
	EVENT_TYPE type;
	DWORD_PTR param1;
	DWORD_PTR param2;
};


//이벤트 지연 처리(오브젝트 생성/삭제, 씬 변경 등)
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

