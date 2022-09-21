#pragma once
#include "global.h"
#include "SceneManager.h"
#include "GObject.h"
class GObject;

class Scene
{
	//현재 씬의 오브젝트 리스트
private:
	std::set<GObject*, GObjectPtCompare> gobjects_[static_cast<int>(GROUP_TYPE::END)];
	std::queue<std::pair<GObject*, GROUP_TYPE>> delete_queue_;
	tstring name_;

	HDC hdc_;
	
public:
	Scene()
		: hdc_{ 0 } {};
	Scene(HDC hdc);
	virtual ~Scene(); //자식 쪽의 상속자 호출을 위함
	virtual bool Enter() = 0; //씬이 시작할 때 실행
	void Update();//매 프레임마다 동작할 구문
	void Render(HDC hdc);
	virtual bool Exit() = 0;//씬이 종료될 때 실행

	void AddGObject(GObject* object, GROUP_TYPE type);
	void DeleteGroupObjects(GROUP_TYPE type);
	void DeleteAllObjects();
	const std::set<GObject*, GObjectPtCompare>& GetGroupObjects(GROUP_TYPE group_type) { return gobjects_[static_cast<UINT>(group_type)]; };
	inline HDC get_hdc() { return hdc_; };
	inline void set_name(tstring name) { name_ = name; }
	inline tstring get_name() { return name_; }
};


