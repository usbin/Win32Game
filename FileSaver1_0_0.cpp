#include "FileSaver1_0_0.h"
#include "FileManager.h"
#include "SceneManager.h"
#include "Scene_Tool.h"
#include "Background.h"
#include "Tile.h"
#include "InvisibleWall.h"
#include "Core.h"
#include "resource.h"
#include "RealObjectSprite.h"
#include "Texture.h"
#include "Collider.h"

FileSaver1_0_0::FileSaver1_0_0() {};
FileSaver1_0_0::~FileSaver1_0_0() {};

void FileSaver1_0_0::SaveTilemapToFile(FILE* p_file)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;
	const std::vector<GObject*>& tiles = scene->GetGroupObjects(GROUP_TYPE::TILE);
	for (int i = 0; i < tiles.size(); i++) {
		SaveTile(p_file, dynamic_cast<Tile*>(tiles[i]));
	}

}

void FileSaver1_0_0::LoadTilemapFromFile(FILE* p_file)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;
	int tiles_size;
	fread(&tiles_size, sizeof(int), 1, p_file);
	for (int i = 0; i < tiles_size; i++) {
		Tile* tile = nullptr;
		LoadTile(p_file, &tile);
		CreateGObject(tile, GROUP_TYPE::TILE);
	}
}

void FileSaver1_0_0::SaveWallToFile(FILE* p_file)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;
	const std::vector<GObject*>& walls = scene->GetGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
	UINT walls_size = walls.size();
	fwrite(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls.size(); i++) {
		SaveWall(p_file, dynamic_cast<InvisibleWall*>(walls[i]));
	}
}

void FileSaver1_0_0::LoadWallFromFile(FILE* p_file)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;
	UINT walls_size;
	fread(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls_size; i++) {
		InvisibleWall* wall = nullptr;
		LoadWall(p_file, &wall);
		CreateGObject(wall, GROUP_TYPE::INVISIBLE_WALL);
	}
}

void FileSaver1_0_0::SaveMapToFile(FILE* p_file)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	const std::vector<GObject*>& bgs1 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND1);
	const std::vector<GObject*>& bgs2 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND2);
	const std::vector<GObject*>& bgs3 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND3);
	const std::vector<GObject*>& walls = scene->GetGroupObjects(GROUP_TYPE::INVISIBLE_WALL);


	//BACKGROUND는 레이어당 반드시 하나만 있음.
	//1. BACKGROUND 저장
	GObject* bg = bgs1.empty() ? nullptr : bgs1[0];
	fwrite(&bg, sizeof(DWORD_PTR), 1, p_file);
	if (bg) {
		//기본 정보, 스프라이트
		SaveBackground(p_file, dynamic_cast<Background*>(bg));
	}
	GObject* bg2 = bgs2.empty() ? nullptr : bgs2[0];
	fwrite(&bg2, sizeof(DWORD_PTR), 1, p_file);
	if (bg2) {
		SaveBackground(p_file, dynamic_cast<Background*>(bg2));
	}
	GObject* bg3 = bgs3.empty() ? nullptr : bgs3[0];
	fwrite(&bg3, sizeof(DWORD_PTR), 1, p_file);
	if (bg3) {

		SaveBackground(p_file, dynamic_cast<Background*>(bg3));
	}
	//2. INVISIBLE_WALL 개수, INVISIBLE_WALL 저장
	UINT walls_size = walls.size();
	fwrite(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls.size(); i++) {
		SaveWall(p_file, dynamic_cast<InvisibleWall*>(walls[i]));
	}
}

void FileSaver1_0_0::LoadMapFromFile(FILE* p_file)
{

	HMENU hmenu = GetMenu(Core::GetInstance()->get_main_hwnd());

	//BACKGROUND는 반드시 하나만 있음.
	//1. BACKGROUND 로드
	Background* bg;
	fread(&bg, sizeof(DWORD_PTR), 1, p_file);
	if (bg) {
		LoadBackground(p_file, &bg);
		CreateGObject(bg, GROUP_TYPE::BACKGROUND1);

		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER1, MF_ENABLED);

	}
	Background* bg2;
	fread(&bg2, sizeof(DWORD_PTR), 1, p_file);
	if (bg2) {
		LoadBackground(p_file, &bg2);
		CreateGObject(bg2, GROUP_TYPE::BACKGROUND2);
		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER2, MF_ENABLED);
	}
	Background* bg3;
	fread(&bg3, sizeof(DWORD_PTR), 1, p_file);
	if (bg3) {
		LoadBackground(p_file, &bg3);
		CreateGObject(bg3, GROUP_TYPE::BACKGROUND3);
		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER3, MF_ENABLED);
	}

	//2. Invisible Wall 로드
	UINT walls_size;
	fread(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls_size; i++) {
		InvisibleWall* wall = nullptr;
		LoadWall(p_file, &wall);
		CreateGObject(wall, GROUP_TYPE::INVISIBLE_WALL);
	}
}



void FileSaver1_0_0::SaveGObject(FILE* p_file, GObject* gobject)
{
	tstring name = gobject->get_name();
	Vector2 pos = gobject->get_pos();
	Vector2 scale = gobject->get_scale();
	GROUP_TYPE group_type = gobject->get_group_type();
	bool is_visible = gobject->get_visible();
	DIRECTION direction = gobject->get_direction();

	int name_size = _tcslen(name.c_str()) + 1;
	fwrite(&name_size, sizeof(int), 1, p_file);
	fwrite((name.c_str()), sizeof(TCHAR), name_size, p_file);
	fwrite(&pos, sizeof(Vector2), 1, p_file);
	fwrite(&group_type, sizeof(Vector2), 1, p_file);
	fwrite(&is_visible, sizeof(bool), 1, p_file);
	fwrite(&direction, sizeof(DIRECTION), 1, p_file);
}

void FileSaver1_0_0::LoadGObject(FILE* p_file, GObject** gobject)
{
	tstring name;
	TCHAR name_buffer[256];
	Vector2 pos;
	Vector2 scale;
	GROUP_TYPE group_type;
	bool is_visible;
	DIRECTION direction;

	int name_size;
	fread(&name_size, sizeof(int), 1, p_file);
	fread(name_buffer, sizeof(TCHAR), name_size, p_file);
	name = tstring(name_buffer);
	fread(&pos, sizeof(Vector2), 1, p_file);
	fread(&group_type, sizeof(Vector2), 1, p_file);
	fread(&is_visible, sizeof(bool), 1, p_file);
	fread(&direction, sizeof(DIRECTION), 1, p_file);
	(*gobject)->set_name(name);
	(*gobject)->set_pos(pos);
	(*gobject)->set_scale(scale);
	(*gobject)->set_group_type(group_type);
	(*gobject)->set_visible(is_visible);
	(*gobject)->set_direction(direction);
}

void FileSaver1_0_0::SaveSprite(FILE* p_file, Sprite* sprite)
{ 
	Texture* texture = sprite->get_texture();
	fwrite(&texture, sizeof(DWORD_PTR), 1, p_file);
	if (texture)	SaveTexture(p_file, texture);
	Vector2 base_pos = sprite->get_base_pos();
	Vector2 scale = sprite->get_scale();
	fwrite(&base_pos, sizeof(Vector2), 1, p_file);
	fwrite(&scale, sizeof(Vector2), 1, p_file);

}

void FileSaver1_0_0::LoadSprite(FILE* p_file, Sprite** sprite, GObject* owner)
{

	Texture* texture;
	fread(&texture, sizeof(DWORD_PTR), 1, p_file);
	if (texture) LoadTexture(p_file, &texture);
	Vector2 base_pos;
	Vector2 scale;
	fread(&base_pos, sizeof(Vector2), 1, p_file);
	fread(&scale, sizeof(Vector2), 1, p_file);
	(*sprite)->QuickSet(texture, owner, base_pos, scale);
}

void FileSaver1_0_0::SaveTexture(FILE* p_file, Texture* texture)
{
	tstring key = texture->get_key();
	tstring relative_path = texture->get_relative_path();
	int key_size = key.length() + 1;
	int relative_path_size = relative_path.length() + 1;
	fwrite(&key_size, sizeof(int), 1, p_file);
	fwrite(key.c_str(), sizeof(TCHAR), key_size, p_file);
	fwrite(&relative_path_size, sizeof(int), 1, p_file);
	fwrite(relative_path.c_str(), sizeof(TCHAR), relative_path_size, p_file);

}

void FileSaver1_0_0::LoadTexture(FILE* p_file, Texture** texture)
{
	
	TCHAR key_buffer[256];
	TCHAR relative_path_buffer[256];
	int key_size;
	int relative_path_size;
	fread(&key_size, sizeof(int), 1, p_file);
	fread(key_buffer, sizeof(TCHAR), key_size, p_file);
	fread(&relative_path_size, sizeof(int), 1, p_file);
	fread(relative_path_buffer, sizeof(TCHAR), relative_path_size, p_file);

	tstring key(key_buffer);
	tstring relative_path(relative_path_buffer);
	(*texture) = ResManager::GetInstance()->LoadTexture(key, relative_path);
}

void FileSaver1_0_0::SaveBackground(FILE* p_file, Background* background)
{
	SaveGObject(p_file, background);

	RealObjectRenderComponent* render_cmp = dynamic_cast<RealObjectRenderComponent*>( background->get_render_component() );
	fwrite(&render_cmp, sizeof(DWORD_PTR), 1, p_file);
	if (render_cmp) {
		RealObjectSprite* sprite = dynamic_cast<RealObjectSprite*>(render_cmp->get_sprite());
		fwrite(&sprite, sizeof(DWORD_PTR), 1, p_file);
		if (sprite) SaveSprite(p_file, sprite);
		

	}

}

void FileSaver1_0_0::LoadBackground(FILE* p_file, Background** background)
{
	(*background) = new Background();
	GObject* p_obj = static_cast<GObject*>(*background);
	LoadGObject(p_file, &p_obj);

	RealObjectRenderComponent* render_cmp;
	fread(&render_cmp, sizeof(DWORD_PTR), 1, p_file);
	if (render_cmp) {
		render_cmp = new RealObjectRenderComponent(*background);

		RealObjectSprite* sprite;
		fread(&sprite, sizeof(DWORD_PTR), 1, p_file);
		
		if (sprite) {
			sprite = new RealObjectSprite();
			Sprite* p_sprite = static_cast<Sprite*>(sprite);
			LoadSprite(p_file, &p_sprite, *background);
			render_cmp->ChangeSprite(sprite);
		}
		(*background)->set_render_component(render_cmp);
	}
}

void FileSaver1_0_0::SaveWall(FILE* p_file, InvisibleWall* wall)
{
	SaveGObject(p_file, wall);
	//콜라이더 저장
	Collider* collider = wall->get_collider();
	fwrite(&collider, sizeof(DWORD_PTR), 1, p_file);
	if (collider) {
		Vector2 pos_offset = collider->get_pos_offset();
		Vector2 scale = collider->get_scale();
		bool is_physical_collider = collider->get_is_physical_collider();
		fwrite(&pos_offset, sizeof(Vector2), 1, p_file);
		fwrite(&scale, sizeof(Vector2), 1, p_file);
		fwrite(&is_physical_collider, sizeof(bool), 1, p_file);
	}

}

void FileSaver1_0_0::LoadWall(FILE* p_file, InvisibleWall** wall)
{
	(*wall) = new InvisibleWall();
	GObject* p_obj = static_cast<GObject*>(*wall);
	LoadGObject(p_file, &p_obj);

	Vector2 pos_offset;		
	Vector2 scale;
	bool is_physical_collider;

	Collider* collider = (*wall)->get_collider();
	fread(&collider, sizeof(DWORD_PTR), 1, p_file);
	if (collider) {
		collider = new Collider();
		Vector2 pos_offset = collider->get_pos_offset();
		Vector2 scale = collider->get_scale();
		bool is_physical_collider = collider->get_is_physical_collider();
		fread(&pos_offset, sizeof(Vector2), 1, p_file);
		fread(&scale, sizeof(Vector2), 1, p_file);
		fread(&is_physical_collider, sizeof(bool), 1, p_file);
		collider->set_owner(*wall);
		collider->set_pos_offset(pos_offset);
		collider->set_scale(scale);
		collider->set_is_physical_collider(is_physical_collider);
		(*wall)->set_collider(collider);
	}
}

void FileSaver1_0_0::SaveTile(FILE* p_file, Tile* tile)
{
	
	SaveGObject(p_file, tile);
	RealObjectRenderComponent* render_cmp = dynamic_cast<RealObjectRenderComponent*>(tile->get_render_component());
	fwrite(&render_cmp, sizeof(DWORD_PTR), 1, p_file);
	if (render_cmp) {
		RealObjectSprite* sprite = dynamic_cast<RealObjectSprite*>(render_cmp->get_sprite());
		fwrite(&sprite, sizeof(DWORD_PTR), 1, p_file);
		if (sprite) SaveSprite(p_file, sprite);


	}
}

void FileSaver1_0_0::LoadTile(FILE* p_file, Tile** tile)
{
	(*tile) = new Tile();
	GObject* p_obj = static_cast<GObject*>(*tile);
	LoadGObject(p_file, &p_obj);

	RealObjectRenderComponent* render_cmp;
	fread(&render_cmp, sizeof(DWORD_PTR), 1, p_file);
	if (render_cmp) {
		render_cmp = new RealObjectRenderComponent(*tile);

		RealObjectSprite* sprite;
		fread(&sprite, sizeof(DWORD_PTR), 1, p_file);

		if (sprite) {
			sprite = new RealObjectSprite();
			Sprite* p_sprite = static_cast<Sprite*>(sprite);
			LoadSprite(p_file, &p_sprite, *tile);
			render_cmp->ChangeSprite(sprite);
		}
		(*tile)->set_render_component(render_cmp);
	}
}
