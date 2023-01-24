#pragma once
#include "global.h"

class Core;
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

	//씬 변경 시 Exit 후 한 프레임 쉬고 다음 프레임에 Enter하도록 함.
	bool change_scene_reserved_ = false;
	SCENE_TYPE reserved_scene_ = SCENE_TYPE::END;
	void ExecuteEvent(Event _event);
public:
	void Update();
	void AddEvent(Event _event);


	friend class Core;
};

