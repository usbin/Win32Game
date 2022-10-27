#include "Scene.h"
#include "KeyManager.h"
#include "RealObject.h"
#include "Tile.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

Scene::Scene(HDC hdc)
	: name_(_T(""))
	, hdc_(hdc)
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

void Scene::CreateTile(UINT column_count, UINT row_count)
{
	for (UINT i = 0; i < tile_map_.size(); i++) {
		SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TILE);
	}

	for (UINT i = 0; i < row_count; i++) {
		for (UINT j = 0; j < column_count; j++) {
			Tile* tile = new Tile();
			tile->set_pos(Vector2{ (static_cast<int>(j * TILE_WIDTH)) % static_cast<int>(column_count * TILE_WIDTH), static_cast<int>((i * TILE_HEIGHT)) });
			tile->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
			tile->set_group_type(GROUP_TYPE::TILE);
			tile->set_name(_T("Tile"));
			CreateGObject(tile, GROUP_TYPE::TILE);
			tile_map_.push_back(tile);
		}
	}

}

Tile* Scene::GetTile(Vector2 world_pos)
{
	//몇번째 타일맵인지 찾고 삽입
	for (int i = 0; i < tile_map_.size(); i++) {
		Vector2 tile_pos = tile_map_[i]->get_pos();
		Vector2 tile_scale = tile_map_[i]->get_scale();
		if (tile_pos.x < world_pos.x && world_pos.x < tile_pos.x + tile_scale.x
			&& tile_pos.y < world_pos.y && world_pos.y < tile_pos.y + tile_scale.y) {
			if (tile_map_[i] == nullptr) {
				int a = 0;
			}
			return tile_map_[i];
		}
	}
	return nullptr;
}
