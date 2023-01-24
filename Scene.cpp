#include "Scene.h"
#include "KeyManager.h"
#include "RealObject.h"
#include "Tile.h"
#include "Core.h"
#include "TileObject.h"

Scene::Scene(ID3D11Device* p_d3d_device)
	: name_(_T(""))
	, p_d3d_device_(p_d3d_device)
	, hdc_(0)

{

}


Scene::~Scene() {
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		DeleteGroupObjects(static_cast<GROUP_TYPE>(group));
	}
}

void Scene::Update()
{
	for (int group = 0; group < static_cast<int>(GROUP_TYPE::END); group++) {
		for (auto gobject : gobjects_[group]) {
			if(!gobject->IsDead() && gobject->get_enabled())
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
				if((*iter)->get_enabled() && (*iter)->get_visible())
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

void Scene::EnableAllObjects()
{
	for (UINT group = 0; group < static_cast<UINT>(GROUP_TYPE::END); group++) {
		for (auto iter : gobjects_[group]) {
			iter->set_enabled(true);
		}
	}
}

void Scene::DisableAllObjects()
{
	for (UINT group = 0; group < static_cast<UINT>(GROUP_TYPE::END); group++) {
		for (auto iter : gobjects_[group]) {
			iter->set_enabled(false);
		}
	}
}


void Scene::GetTileObject(const Vector2& pos, Vector2& out_base_pos, TileObject*& out_tile_object)
{
	const std::vector<GObject*>& tile_objects = GetGroupObjects(GROUP_TYPE::TILE_OBJECT);
	for (int i = 0; i < tile_objects.size(); i++) {
		Vector2 tile_object_pos = tile_objects[i]->get_pos();
		Vector2 tile_object_scale = tile_objects[i]->get_scale();
		if (tile_object_pos.x - tile_object_scale.x / 2.f <= pos.x
			&& tile_object_pos.x + tile_object_scale.x / 2.f > pos.x
			&& tile_object_pos.y - tile_object_scale.y / 2.f <= pos.y
			&& tile_object_pos.y + tile_object_scale.y / 2.f > pos.y)
		{
			if (!tile_objects[i]->IsDead()) {
				out_tile_object = dynamic_cast<TileObject*>(tile_objects[i]);
				out_base_pos.x = out_tile_object->get_pos().x;
				out_base_pos.y = out_tile_object->get_pos().y;
				return;
			}
			

		}
	}
	out_tile_object = nullptr;
	out_base_pos.x = (int)pos.x - ((int)pos.x % (int)TILE_WIDTH) + TILE_WIDTH/2;
	out_base_pos.y = (int)pos.y - ((int)pos.y % (int)TILE_HEIGHT) + TILE_HEIGHT/2;


}

void Scene::GetTilePos(const Vector2& pos, Vector2& out_base_pos)
{
	out_base_pos.x = (int)pos.x - ((int)pos.x % (int)TILE_WIDTH) + TILE_WIDTH / 2;
	out_base_pos.y = (int)pos.y - ((int)pos.y % (int)TILE_HEIGHT) + TILE_HEIGHT / 2;

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