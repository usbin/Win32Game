#include "FileManager.h"
#include "SceneManager.h"
#include "Scene_Tool.h"
#include "Background.h"
#include "Tile.h"
#include "InvisibleWall.h"
#include "Core.h"
#include "resource.h"
#include "FileSaver1_1_0.h"
FileManager::FileManager() {
	file_saver_ = DEBUG_NEW FileSaver1_1_0();
	old_saver_ = DEBUG_NEW FileSaver1_0_0();
};
FileManager::~FileManager() {
	delete file_saver_;
	delete old_saver_;
};

void FileManager::SaveMap(const tstring& file_path)
{
	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("wb"));
	assert(p_file);

	file_saver_->SaveMapToFile(p_file);

	fclose(p_file);
	

}

void FileManager::LoadMap(const tstring& file_path)
{

	HMENU hmenu = GetMenu(Core::GetInstance()->get_main_hwnd());

	EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER1, MF_DISABLED);
	EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER2, MF_DISABLED);
	EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER3, MF_DISABLED);
	EnableMenuItem(hmenu, IDM_REMOVE_TOPGROUND, MF_DISABLED);


	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("rb"));
	if (!p_file) {
		return;
	}

	file_saver_->LoadMapFromFile(p_file);

	fclose(p_file);


}

void FileManager::SaveWallFile(const tstring& file_path)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("wb"));
	assert(p_file);

	const std::vector<GObject*>& walls = scene->GetGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
	UINT walls_size = walls.size();
	fwrite(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls.size(); i++) {
		file_saver_->SaveWall(p_file, dynamic_cast<InvisibleWall*>(walls[i]));
	}

	fclose(p_file);
}

void FileManager::LoadWallFile(const tstring& file_path)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("rb"));
	if (!p_file) return;

	UINT walls_size;
	fread(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls_size; i++) {
		InvisibleWall* wall = file_saver_->LoadWall(p_file);
		CreateGObject(wall, GROUP_TYPE::INVISIBLE_WALL);
	}

	fclose(p_file);
}

void FileManager::SaveTilemapFile(const tstring& file_path)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("wb"));
	assert(p_file);

	const std::vector<GObject*>& tiles = scene->GetGroupObjects(GROUP_TYPE::TILE);

	UINT tiles_size = tiles.size();
	fwrite(&tiles_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < tiles.size(); i++) {
		file_saver_->SaveTile(p_file, dynamic_cast<Tile*>(tiles[i]));

	}
	fclose(p_file);
}

void FileManager::LoadTilemapFile(const tstring& file_path)
{
	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("rb"));
	if (!p_file) return;

	UINT tiles_size;
	fread(&tiles_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < tiles_size; i++) {
		Tile* tile = file_saver_->LoadTile(p_file);
		CreateGObject(tile, GROUP_TYPE::TILE);

	}
	fclose(p_file);

}
