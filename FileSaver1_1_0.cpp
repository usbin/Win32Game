#include "FileSaver1_1_0.h"
#include "RealObjectRenderComponent.h"
#include "Topground.h"
#include "Scene_Tool.h"
#include "Background.h"
#include "InvisibleWall.h"
#include "Core.h"
#include "resource.h"

void FileSaver1_1_0::SaveTopground(FILE* p_file, Topground* topground)
{
	SaveGObject(p_file, topground);

	RealObjectRenderComponent* render_cmp = dynamic_cast<RealObjectRenderComponent*>(topground->get_render_component());
	fwrite(&render_cmp, sizeof(DWORD_PTR), 1, p_file);
	if (render_cmp) {
		RealObjectSprite* sprite = dynamic_cast<RealObjectSprite*>(render_cmp->get_sprite());
		fwrite(&sprite, sizeof(DWORD_PTR), 1, p_file);
		if (sprite) SaveGObjectSprite(p_file, sprite);


	}
}

Topground* FileSaver1_1_0::LoadTopground(FILE* p_file)
{
	Topground* topground = DEBUG_NEW Topground();
	GObject* p_obj = static_cast<GObject*>(topground);
	LoadGObject(p_file, p_obj);

	RealObjectRenderComponent* render_cmp;
	fread(&render_cmp, sizeof(DWORD_PTR), 1, p_file);
	if (render_cmp) {
		render_cmp = DEBUG_NEW RealObjectRenderComponent(topground);

		RealObjectSprite* sprite;
		fread(&sprite, sizeof(DWORD_PTR), 1, p_file);

		if (sprite) {
			sprite = DEBUG_NEW RealObjectSprite();
			GObjectSprite* p_sprite = static_cast<GObjectSprite*>(sprite);
			LoadGObjectSprite(p_file, p_sprite, topground);
			render_cmp->ChangeSprite(sprite);
		}
		render_cmp->set_render_layer(RENDER_LAYER::PLAYER);
		if (topground->get_render_component()) delete topground->get_render_component();
		topground->set_render_component(render_cmp);
	}
	return topground;
}

void FileSaver1_1_0::SaveMapToFile(FILE* p_file)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	const std::vector<GObject*>& bgs1 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND1);
	const std::vector<GObject*>& bgs2 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND2);
	const std::vector<GObject*>& bgs3 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND3);
	const std::vector<GObject*>& tgs = scene->GetGroupObjects(GROUP_TYPE::TOPGROUND);
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
	GObject* tg = tgs.empty() ? nullptr : tgs[0];
	fwrite(&tg, sizeof(DWORD_PTR), 1, p_file);
	if (tg) {
		SaveTopground(p_file, dynamic_cast<Topground*>(tg));
	}
	//2. INVISIBLE_WALL 개수, INVISIBLE_WALL 저장
	UINT walls_size = walls.size();
	fwrite(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls.size(); i++) {
		SaveWall(p_file, dynamic_cast<InvisibleWall*>(walls[i]));
	}
}

void FileSaver1_1_0::LoadMapFromFile(FILE* p_file)
{
	HMENU hmenu = GetMenu(Core::GetInstance()->get_main_hwnd());

	//BACKGROUND는 반드시 하나만 있음.
	//1. BACKGROUND 로드
	Background* bg;
	fread(&bg, sizeof(DWORD_PTR), 1, p_file);
	if (bg) {
		bg = LoadBackground(p_file);
		CreateGObject(bg, GROUP_TYPE::BACKGROUND1);
		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER1, MF_ENABLED);

	}
	Background* bg2;
	fread(&bg2, sizeof(DWORD_PTR), 1, p_file);
	if (bg2) {
		bg2 = LoadBackground(p_file);
		CreateGObject(bg2, GROUP_TYPE::BACKGROUND2);
		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER2, MF_ENABLED);
	}
	Background* bg3;
	fread(&bg3, sizeof(DWORD_PTR), 1, p_file);
	if (bg3) {
		bg3 = LoadBackground(p_file);
		CreateGObject(bg3, GROUP_TYPE::BACKGROUND3);
		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER3, MF_ENABLED);
	}
	Topground* tg;
	fread(&tg, sizeof(DWORD_PTR), 1, p_file);
	if (tg) {
		tg = LoadTopground(p_file);
		CreateGObject(tg, GROUP_TYPE::TOPGROUND);
		EnableMenuItem(hmenu, IDM_REMOVE_TOPGROUND, MF_ENABLED);
	}

	//2. Invisible Wall 로드
	UINT walls_size;
	fread(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls_size; i++) {
		InvisibleWall* wall = LoadWall(p_file);
		CreateGObject(wall, GROUP_TYPE::INVISIBLE_WALL);
	}
}

