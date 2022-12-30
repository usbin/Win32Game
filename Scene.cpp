#include "Scene.h"
#include "KeyManager.h"
#include "RealObject.h"
#include "Tile.h"


Scene::Scene(ID3D11Device* p_d3d_device)
	: name_(_T(""))
	, p_d3d_device_(p_d3d_device)
{

}


Scene::~Scene() {
	//DeleteAllObjects();
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		for (auto gobject : gobjects_[group]) {
			delete gobject;
		}
		gobjects_[group].clear();
	}
}

void Scene::Update()
{
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		for (auto gobject : gobjects_[group]) {
			if(!gobject->IsDead())
				gobject->Update();
		}
	}
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		for (auto gobject : gobjects_[group]) {
			gobject->FinalUpdate();
		}
	}


	
}
void Scene::Render(ID3D11Device* p_d3d_device)
{
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		auto iter = gobjects_[group].begin();
		while (iter != gobjects_[group].end()) {
			if (!(*iter)->IsDead()) {
				(*iter)->Render(p_d3d_device);
				iter++;
			}
			else {
				iter = gobjects_[group].erase(iter);
			}
		}
	}
}

void Scene::AddGObject(GObject* object, GROUP_TYPE type)
{
	gobjects_[static_cast<UINT>(type)].push_back(object);
}

void Scene::RemoveGObject(GObject* object, GROUP_TYPE type)
{
	std::vector<GObject*>::iterator iter = find(gobjects_[static_cast<UINT>(type)].begin(), gobjects_[static_cast<UINT>(type)].end(), object);
	if (iter != gobjects_[static_cast<UINT>(type)].end()) {
		gobjects_[static_cast<UINT>(type)].erase(iter);
	}
}

void Scene::DeleteGroupObjects(GROUP_TYPE type)
{
	for (auto obj : gobjects_[static_cast<UINT>(type)]) {
		DeleteGObject(obj, type);

	}
	gobjects_[static_cast<UINT>(type)].clear();

}
void Scene::DeleteAllObjects()
{
	for (UINT i = 0; i < static_cast<UINT>(GROUP_TYPE::END); i++) {
		DeleteGroupObjects(static_cast<GROUP_TYPE>(i));
	}
}

void Scene::ObjectToTop(GROUP_TYPE group_type, GObject* target)
{
	auto iter = std::find(gobjects_[static_cast<UINT>(group_type)].begin(), gobjects_[static_cast<UINT>(group_type)].end(), target);
	if (iter != gobjects_[static_cast<UINT>(group_type)].end()) {
		gobjects_[static_cast<UINT>(group_type)].erase(iter);
		gobjects_[static_cast<UINT>(group_type)].push_back(target);
	}
}

void Scene::ObjectToPrev(GROUP_TYPE group_type, GObject* target)
{
	auto iter = std::find(gobjects_[static_cast<UINT>(group_type)].begin(), gobjects_[static_cast<UINT>(group_type)].end(), target);
	if (iter != gobjects_[static_cast<UINT>(group_type)].end()) {
		gobjects_[static_cast<UINT>(group_type)].erase(iter);
		gobjects_[static_cast<UINT>(group_type)].insert(iter-1, target);
	}
}

void Scene::ObjectToNext(GROUP_TYPE group_type, GObject* target)
{
	auto iter = std::find(gobjects_[static_cast<UINT>(group_type)].begin(), gobjects_[static_cast<UINT>(group_type)].end(), target);
	if (iter != gobjects_[static_cast<UINT>(group_type)].end()) {
		gobjects_[static_cast<UINT>(group_type)].erase(iter);
		gobjects_[static_cast<UINT>(group_type)].insert(iter +1, target);
	}
}