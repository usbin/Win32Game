#include "TileObjectDb.h"
#include "NaturalThing.h"
#include "Field.h"
#include "TileObjectSprite.h"
#include "ResManager.h"
TileObjectDb::TileObjectDb() {

}
TileObjectDb::~TileObjectDb() {
	for (int i = 0; i < (int)TILE_OBJECT_TYPE::END; i++) {
		delete tile_object_infos[i];
	}
}

void TileObjectDb::Init()
{
	Texture* wood_texture = ResManager::GetInstance()->LoadTexture(_T("Wood"), _T("texture\\StardewValley_Tree.png"));
	Texture* stone_weed_texture = ResManager::GetInstance()->LoadTexture(_T("StoneWeed"), _T("texture\\StardewValley_Mine.png"));
	Texture* field_texture = ResManager::GetInstance()->LoadTexture(_T("Field"), _T("texture\\StardewValley_Field.png"));
	NaturalThing* wood = DEBUG_NEW NaturalThing();
	TileObjectSprite* wood_sprite = DEBUG_NEW TileObjectSprite();
	wood_sprite->QuickSet(wood_texture, nullptr, Vector2{ 49, 123 }, Vector2{ 16, 20 });
	wood->Init(TILE_OBJECT_TYPE::WOOD, _T("나무"), wood_sprite);
	

	NaturalThing* stone = DEBUG_NEW NaturalThing();
	TileObjectSprite* stone_sprite = DEBUG_NEW TileObjectSprite();
	stone_sprite->QuickSet(stone_weed_texture, nullptr, Vector2{ 365, 1 }, Vector2{ 16, 16 });
	stone->Init(TILE_OBJECT_TYPE::STONE, _T("돌"), stone_sprite);

	NaturalThing* weed = DEBUG_NEW NaturalThing();
	TileObjectSprite* weed_sprite = DEBUG_NEW TileObjectSprite();
	weed_sprite->QuickSet(stone_weed_texture, nullptr, Vector2{ 202, 199 }, Vector2{ 16, 16 });
	weed->Init(TILE_OBJECT_TYPE::WEED, _T("잡초"), weed_sprite);

	Field* field = DEBUG_NEW Field();
	TileObjectSprite* field_sprites[2][16] = { nullptr };
	field_sprites[false][0] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_UP] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_RIGHT] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_DOWN] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_LEFT] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_UP | FIELD_CONNECTED_DOWN] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_RIGHT] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT] = DEBUG_NEW TileObjectSprite();
	field_sprites[false][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT] = DEBUG_NEW TileObjectSprite();

	field_sprites[false][0]->QuickSet(field_texture, nullptr, Vector2{ 0, 0 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_UP]->QuickSet(field_texture, nullptr, Vector2{ 0, 48 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_RIGHT]->QuickSet(field_texture, nullptr, Vector2{ 16, 48 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_DOWN]->QuickSet(field_texture, nullptr, Vector2{ 0, 16 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_LEFT]->QuickSet(field_texture, nullptr, Vector2{ 48, 48 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT]->QuickSet(field_texture, nullptr, Vector2{ 16, 32 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN]->QuickSet(field_texture, nullptr, Vector2{ 16, 0 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT]->QuickSet(field_texture, nullptr, Vector2{ 48, 0 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP]->QuickSet(field_texture, nullptr, Vector2{ 48, 32 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_UP | FIELD_CONNECTED_DOWN]->QuickSet(field_texture, nullptr, Vector2{ 0, 32 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_RIGHT]->QuickSet(field_texture, nullptr, Vector2{ 32, 48 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN]->QuickSet(field_texture, nullptr, Vector2{ 16, 16 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT]->QuickSet(field_texture, nullptr, Vector2{ 32, 0 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP]->QuickSet(field_texture, nullptr, Vector2{ 48, 16 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT]->QuickSet(field_texture, nullptr, Vector2{ 32, 32 }, Vector2{ 16, 16 });
	field_sprites[false][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT]->QuickSet(field_texture, nullptr, Vector2{ 32, 16 }, Vector2{ 16, 16 });

	field_sprites[true][0] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_UP] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_RIGHT] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_DOWN] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_LEFT] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_UP | FIELD_CONNECTED_DOWN] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_RIGHT] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT] = DEBUG_NEW TileObjectSprite();
	field_sprites[true][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT] = DEBUG_NEW TileObjectSprite();

	field_sprites[true][0]->QuickSet(field_texture, nullptr, Vector2{ 0+64, 0 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_UP]->QuickSet(field_texture, nullptr, Vector2{ 0+64, 48 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_RIGHT]->QuickSet(field_texture, nullptr, Vector2{ 16+64, 48 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_DOWN]->QuickSet(field_texture, nullptr, Vector2{ 0+64, 16 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_LEFT]->QuickSet(field_texture, nullptr, Vector2{ 48+64, 48 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT]->QuickSet(field_texture, nullptr, Vector2{ 16+64, 32 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN]->QuickSet(field_texture, nullptr, Vector2{ 16+64, 0 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT]->QuickSet(field_texture, nullptr, Vector2{ 48+64, 0 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP]->QuickSet(field_texture, nullptr, Vector2{ 48+64, 32 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_UP | FIELD_CONNECTED_DOWN]->QuickSet(field_texture, nullptr, Vector2{ 0+64, 32 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_RIGHT]->QuickSet(field_texture, nullptr, Vector2{ 32+64, 48 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN]->QuickSet(field_texture, nullptr, Vector2{ 16+64, 16 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT]->QuickSet(field_texture, nullptr, Vector2{ 32+64, 0 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP]->QuickSet(field_texture, nullptr, Vector2{ 48+64, 16 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_LEFT | FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT]->QuickSet(field_texture, nullptr, Vector2{ 32+64, 32 }, Vector2{ 16, 16 });
	field_sprites[true][FIELD_CONNECTED_UP | FIELD_CONNECTED_RIGHT | FIELD_CONNECTED_DOWN | FIELD_CONNECTED_LEFT]->QuickSet(field_texture, nullptr, Vector2{ 32+64, 16 }, Vector2{ 16, 16 });
	
	for (int i = 0; i < 16; i++) {
		field->SetSprite(false, i, field_sprites[false][i]);
		field->SetSprite(true, i, field_sprites[true][i]);
	}

	tile_object_infos[(int)TILE_OBJECT_TYPE::WOOD] = wood;
	tile_object_infos[(int)TILE_OBJECT_TYPE::STONE] = stone;
	tile_object_infos[(int)TILE_OBJECT_TYPE::WEED] = weed;
	tile_object_infos[(int)TILE_OBJECT_TYPE::FIELD] = field;

}
