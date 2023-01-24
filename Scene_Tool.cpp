#include "Scene_Tool.h"
#include "Director_Scene_Tool.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "TileUi.h"
#include "ResManager.h"
#include "GObjectSprite.h"
#include "CollisionManager.h"
#include "Core.h"
#include "Tile.h"
#include "TileEditUi.h"
#include "Game.h"
Scene_Tool::Scene_Tool()
	:hdc_(0)
{
}

Scene_Tool::Scene_Tool(ID3D11Device* p_d3d_device)
	: Scene(p_d3d_device)
{
}


Scene_Tool::~Scene_Tool()
{
	
}

bool Scene_Tool::Enter(SCENE_TYPE from)
{

	//Camera::GetInstance()->set_look_pos(Vector2{ 0, 0 });

	Director_Scene_Tool* dst = DEBUG_NEW Director_Scene_Tool();
	dst->set_group_type(GROUP_TYPE::DIRECTOR);
	CreateGObject(dst, GROUP_TYPE::DIRECTOR);
	director_ = dst;

	Texture* farm_texture = ResManager::GetInstance()->LoadTexture(_T("Stardew Valley Farm"), _T("texture\\StardewValley_FarmSpring.png"));


	//화면에 기본 80x65칸 빈 타일맵 만들기
	CreateEmptyTilemap(80, 65);

	GObject* gobj = DEBUG_NEW Player();
	gobj->set_pos(Vector2{ 0, 0 });
	gobj->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(gobj, GROUP_TYPE::PLAYER);

	Camera::GetInstance()->set_target(gobj);
	Camera::GetInstance()->unset_limit();


	return true;
}

bool Scene_Tool::Exit()
{
	SceneManager::GetInstance()->get_current_scene()->DeleteAllObjects();
	return true;
}

void Scene_Tool::CreateEmptyTilemap(UINT column_count, UINT row_count)
{
	SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TILE);
	column_count_ = column_count;
	row_count_ = row_count;
	for (UINT i = 0; i < row_count; i++) {
		for (UINT j = 0; j < column_count; j++) {
			Tile* tile = DEBUG_NEW Tile();
			tile->set_pos(Vector2{ (static_cast<int>(j * TILE_WIDTH)) % static_cast<int>(column_count * TILE_WIDTH) + TILE_WIDTH / 2.f, static_cast<int>((i * TILE_HEIGHT)) + TILE_HEIGHT / 2.f });
			tile->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
			tile->set_group_type(GROUP_TYPE::TILE);
			tile->set_name(_T("Tile"));
			CreateGObject(tile, GROUP_TYPE::TILE);
		}
	}
}

void Scene_Tool::ChangeTileuisTexture(Texture* tileuis_texture, Vector2 texture_base_pos, Vector2 texture_scale, Vector2 sprite_scale, Vector2 interval, int count)
{
	tileuis_texture_ = tileuis_texture;
	texture_base_pos_ = texture_base_pos;
	texture_scale_ = texture_scale;
	sprite_scale_ = sprite_scale;
	interval_ = interval;
	count_ = count;
	if (director_ && director_->get_tile_edit_ui()) {
		director_->get_tile_edit_ui()->ChangeTileuisTexture(tileuis_texture, texture_base_pos, texture_scale, sprite_scale, interval, count);
	}
}

Tile* Scene_Tool::GetTile(Vector2 world_pos)
{
	const std::vector<GObject*>& tiles = GetGroupObjects(GROUP_TYPE::TILE);
	//몇번째 타일맵인지 찾고 삽입
	for (int i = 0; i < tiles.size(); i++) {
		Vector2 tile_pos = tiles[i]->get_pos();
		Vector2 tile_scale = tiles[i]->get_scale();
		if (tile_pos.x - tile_scale.x / 2.f < world_pos.x && world_pos.x < tile_pos.x + tile_scale.x / 2.f
			&& tile_pos.y - tile_scale.y / 2.f < world_pos.y && world_pos.y < tile_pos.y + tile_scale.y / 2.f) {
			return dynamic_cast<Tile*>(tiles[i]);
		}
	}
	return nullptr;
}
