#pragma once
#include "global.h"
#include "SceneManager.h"
#include "GObject.h"
class GObject;
class Tile;
class Scene
{
	//현재 씬의 오브젝트 리스트
private:
	std::vector<GObject*> gobjects_[static_cast<int>(GROUP_TYPE::END)];
	std::queue<std::pair<GObject*, GROUP_TYPE>> delete_queue_;
	tstring name_;

	HDC hdc_;

	std::vector<Tile*> tile_map_;
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
	void RemoveGObject(GObject* object, GROUP_TYPE type);
	void DeleteGroupObjects(GROUP_TYPE type);
	void DeleteAllObjects();
	inline const std::vector<GObject*>& GetGroupObjects(GROUP_TYPE group_type) { return gobjects_[static_cast<UINT>(group_type)]; };
	void ObjectToTop(GROUP_TYPE group_type, GObject* target);
	void ObjectToPrev(GROUP_TYPE group_type, GObject* target);
	void ObjectToNext(GROUP_TYPE group_type, GObject* target);
	void CreateTile(UINT column_count, UINT row_count);
	Tile* GetTile(Vector2 world_pos); //해당 위치에 있는 타일 리턴. 없으면 nullptr
	inline HDC get_hdc() { return hdc_; };
	inline void set_name(tstring name) { name_ = name; }
	inline tstring get_name() { return name_; }
	inline const std::vector<Tile*>& get_tile_map() { return tile_map_; };
};


