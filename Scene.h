#pragma once
#include "global.h"
#include "SceneManager.h"
#include "GObject.h"
class GObject;
class Tile;
class Scene
{
	//���� ���� ������Ʈ ����Ʈ
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
	virtual ~Scene(); //�ڽ� ���� ����� ȣ���� ����
	virtual bool Enter() = 0; //���� ������ �� ����
	void Update();//�� �����Ӹ��� ������ ����
	void Render(HDC hdc);
	virtual bool Exit() = 0;//���� ����� �� ����

	void AddGObject(GObject* object, GROUP_TYPE type);
	void RemoveGObject(GObject* object, GROUP_TYPE type);
	void DeleteGroupObjects(GROUP_TYPE type);
	void DeleteAllObjects();
	inline const std::vector<GObject*>& GetGroupObjects(GROUP_TYPE group_type) { return gobjects_[static_cast<UINT>(group_type)]; };
	void ObjectToTop(GROUP_TYPE group_type, GObject* target);
	void ObjectToPrev(GROUP_TYPE group_type, GObject* target);
	void ObjectToNext(GROUP_TYPE group_type, GObject* target);
	void CreateTile(UINT column_count, UINT row_count);
	Tile* GetTile(Vector2 world_pos); //�ش� ��ġ�� �ִ� Ÿ�� ����. ������ nullptr
	inline HDC get_hdc() { return hdc_; };
	inline void set_name(tstring name) { name_ = name; }
	inline tstring get_name() { return name_; }
	inline const std::vector<Tile*>& get_tile_map() { return tile_map_; };
};


