#pragma once
#include "global.h"
#include "SceneManager.h"
#include "GObject.h"
class GObject;

class Scene
{
	//���� ���� ������Ʈ ����Ʈ
private:
	std::set<GObject*, GObjectPtCompare> gobjects_[static_cast<int>(GROUP_TYPE::END)];
	std::queue<std::pair<GObject*, GROUP_TYPE>> delete_queue_;
	tstring name_;

	HDC hdc_;
	
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
	void DeleteGroupObjects(GROUP_TYPE type);
	void DeleteAllObjects();
	const std::set<GObject*, GObjectPtCompare>& GetGroupObjects(GROUP_TYPE group_type) { return gobjects_[static_cast<UINT>(group_type)]; };
	inline HDC get_hdc() { return hdc_; };
	inline void set_name(tstring name) { name_ = name; }
	inline tstring get_name() { return name_; }
};


