#include "FileManager.h"
#include "SceneManager.h"
#include "Scene_Tool.h"
#include "Background.h"
#include "Tile.h"
#include "InvisibleWall.h"

FileManager::FileManager() {};
FileManager::~FileManager() {};
void FileManager::SaveMap(const tstring& file_path)
{
	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("wb"));
	assert(p_file);

	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	const std::vector<GObject*> bgs = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND);
	const std::vector<GObject*> tiles = scene->GetGroupObjects(GROUP_TYPE::TILE);
	const std::vector<GObject*> walls = scene->GetGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
	

	//BACKGROUND는 반드시 하나만 있음.
	//1. BACKGROUND 저장
	GObject* bg = bgs.empty() ? nullptr : bgs[0];
	fwrite(&bg, sizeof(DWORD_PTR), 1, p_file);
	if(bg){
		bg->SaveToFile(p_file);
	}
	//2. TILE 개수, TILE 저장
	UINT tiles_size = tiles.size();
	fwrite(&tiles_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i]->SaveToFile(p_file);
	}
	//3. INVISIBLE_WALL 개수, INVISIBLE_WALL 저장
	UINT walls_size = walls.size();
	fwrite(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls.size(); i++) {
		walls[i]->SaveToFile(p_file);
	}

	fclose(p_file);
	

}

void FileManager::LoadMap(const tstring& file_path)
{
	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("rb"));
	assert(p_file);

	//BACKGROUND는 반드시 하나만 있음.
	//1. BACKGROUND 저장
	GObject* bg;
	fread(&bg, sizeof(DWORD_PTR), 1, p_file);
	if (bg) {
		bg = new Background();
		bg->LoadFromFile(p_file);
		CreateGObject(bg, GROUP_TYPE::BACKGROUND);
	}
	
	//2. TILE 개수, TILE 저장
	UINT tiles_size;
	fread(&tiles_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < tiles_size; i++) {
		Tile* tile = new Tile();
		tile->LoadFromFile(p_file);
		CreateGObject(tile, GROUP_TYPE::TILE);

	}
	//3. INVISIBLE_WALL 개수, INVISIBLE_WALL 저장
	UINT walls_size;
	fread(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls_size; i++) {
		InvisibleWall* wall = new InvisibleWall();
		wall->LoadFromFile(p_file);
		CreateGObject(wall, GROUP_TYPE::INVISIBLE_WALL);
	}

	fclose(p_file);


}
