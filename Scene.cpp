#include "Scene.h"
#include "KeyManager.h"


Scene::Scene(HDC hdc)
	: name_(_T(""))
	, hdc_(hdc)
{

}


Scene::~Scene() {
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		for (auto gobject : gobjects_[group]) {
			delete gobject;
		}
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
void Scene::Render(HDC hdc)
{
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		auto iter = gobjects_[group].begin();
		while (iter != gobjects_[group].end()) {
			if (!(*iter)->IsDead()) {
				(*iter)->Render(hdc);
				iter++;
			}
			else {
				iter = gobjects_[group].erase(iter);
			}
		}
	}
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		for (auto gobject : gobjects_[group]) {
			gobject->ComponentRender(hdc);
		}
	}
}

void Scene::AddGObject(GObject* object, GROUP_TYPE type)
{
	gobjects_[static_cast<UINT>(type)].insert(object);
}

void Scene::DeleteGroupObjects(GROUP_TYPE type)
{
	for (auto iter : gobjects_[static_cast<UINT>(type)]) {
		delete iter;

	}
	gobjects_[static_cast<UINT>(type)].clear();

}
void Scene::DeleteAllObjects()
{
	for (UINT i = 0; i < static_cast<UINT>(GROUP_TYPE::END); i++) {
		DeleteGroupObjects(static_cast<GROUP_TYPE>(i));
	}
}
