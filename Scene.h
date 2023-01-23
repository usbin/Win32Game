#pragma once
#include "global.h"
#include "SceneManager.h"
#include "GObject.h"
class GObject;
class Tile;
class TileObject;
class Scene
{
	//현재 씬의 오브젝트 리스트
private:
	std::vector<GObject*> gobjects_[static_cast<int>(GROUP_TYPE::END)];
	std::queue<std::pair<GObject*, GROUP_TYPE>> delete_queue_;
	tstring name_;

	HDC hdc_ = 0;
	ID3D11Device* p_d3d_device_ = nullptr;
	

public:
	Scene()
		: hdc_{ 0 } {};
	Scene(ID3D11Device* p_d3d_device);
	virtual ~Scene(); //자식 쪽의 상속자 호출을 위함
	virtual bool Enter() = 0; //씬이 시작할 때 실행
	void Update();//매 프레임마다 동작할 구문
	void Render(ID3D11Device* p_d3d_device);
	virtual bool Exit() = 0;//씬이 종료될 때 실행

	void AddGObject(GObject* object, GROUP_TYPE type);
	void DeleteGroupObjects(GROUP_TYPE type);
	void DeleteAllObjects();
	inline const std::vector<GObject*>& GetGroupObjects(GROUP_TYPE group_type) { return gobjects_[static_cast<UINT>(group_type)]; };
	void GetTileObject(const Vector2& pos, Vector2& p_out_base_pos, TileObject*& p_out_tile_object );		//해당 위치의 타일 오브젝트를 찾아 위치와 함께 반환/없으면 nullptr
	void GetTilePos(const Vector2& pos, Vector2& p_out_base_pos);
	void ObjectToTop(GROUP_TYPE group_type, GObject* target);
	void ObjectToPrev(GROUP_TYPE group_type, GObject* target);
	void ObjectToNext(GROUP_TYPE group_type, GObject* target);
	inline HDC get_hdc() { return hdc_; };
	inline void set_name(tstring name) { name_ = name; }
	inline tstring get_name() { return name_; }

	
};


