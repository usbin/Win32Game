#pragma once
#include "global.h"
#include "SceneManager.h"
#include "GObject.h"
class GObject;
class Tile;
class TileObject;
class Scene
{
	//���� ���� ������Ʈ ����Ʈ
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
	virtual ~Scene(); //�ڽ� ���� ����� ȣ���� ����
	virtual bool Enter() = 0; //���� ������ �� ����
	void Update();//�� �����Ӹ��� ������ ����
	void Render(ID3D11Device* p_d3d_device);
	virtual bool Exit() = 0;//���� ����� �� ����

	void AddGObject(GObject* object, GROUP_TYPE type);
	void DeleteGroupObjects(GROUP_TYPE type);
	void DeleteAllObjects();
	inline const std::vector<GObject*>& GetGroupObjects(GROUP_TYPE group_type) { return gobjects_[static_cast<UINT>(group_type)]; };
	void GetTileObject(const Vector2& pos, Vector2& p_out_base_pos, TileObject*& p_out_tile_object );		//�ش� ��ġ�� Ÿ�� ������Ʈ�� ã�� ��ġ�� �Բ� ��ȯ/������ nullptr
	void GetTilePos(const Vector2& pos, Vector2& p_out_base_pos);
	void ObjectToTop(GROUP_TYPE group_type, GObject* target);
	void ObjectToPrev(GROUP_TYPE group_type, GObject* target);
	void ObjectToNext(GROUP_TYPE group_type, GObject* target);
	inline HDC get_hdc() { return hdc_; };
	inline void set_name(tstring name) { name_ = name; }
	inline tstring get_name() { return name_; }

	
};


