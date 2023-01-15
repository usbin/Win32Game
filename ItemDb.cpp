#include "ItemDb.h"
#include "Equip.h"
#include "Crop.h"
#include "Mic.h"
#include "Seed.h"
#include "ResManager.h"
#include "ItemSprite.h"
#include "ItemAnimator.h"
#include "ItemAnimation.h"

ItemDb::ItemDb() {};
ItemDb::~ItemDb() {

	SafeDeleteMap<int, IItem*>(items_);
};
void ItemDb::Init()
{
	Equip* hoe = DEBUG_NEW Equip();
	Equip* watering_pot = DEBUG_NEW Equip();
	Equip* pickaxe = DEBUG_NEW Equip();
	Equip* axe = DEBUG_NEW Equip();
	Mic* stone = DEBUG_NEW Mic();
	Mic* weed = DEBUG_NEW Mic();
	Mic* wood = DEBUG_NEW Mic();
	Seed* parsnip_seed = DEBUG_NEW Seed();
	Crop* parsnip = DEBUG_NEW Crop();

	hoe->Init((int)ITEM_CODE::HOE, _T("±ªÀÌ"));
	watering_pot->Init((int)ITEM_CODE::WATERING_POT, _T("¹°»Ñ¸®°³"));
	pickaxe->Init((int)ITEM_CODE::PICKAXE, _T("°î±ªÀÌ"));
	axe->Init((int)ITEM_CODE::AXE, _T("µµ³¢"));
	stone->Init((int)ITEM_CODE::STONE, _T("µ¹"));
	weed->Init((int)ITEM_CODE::WEED, _T("ÀâÃÊ"));
	wood->Init((int)ITEM_CODE::WOOD, _T("³ª¹«"));
	parsnip_seed->Init((int)ITEM_CODE::PARSNIP_SEED, (int)ITEM_CODE::PARSNIP, 5, _T("¼ø¹« ¾¾¾Ñ"));
	parsnip->Init((int)ITEM_CODE::PARSNIP, _T("¼ø¹«"));
	hoe->set_scale(Vector2{ 192, 192 });
	watering_pot->set_scale(Vector2{ 192, 192 });
	pickaxe->set_scale(Vector2{ 192, 192 });
	axe->set_scale(Vector2{ 192, 192 });
	stone->set_scale(Vector2{ 192, 192 });
	weed->set_scale(Vector2{ 192, 192 });
	wood->set_scale(Vector2{ 192, 192 });
	parsnip_seed->set_scale(Vector2{ 32, 32 });
	parsnip->set_scale(Vector2{ 32, 32 });

	Texture* tool_texture = ResManager::GetInstance()->LoadTexture(_T("StardewValley_Tool"), _T("texture\\StardewValley_Tool.png"));
	Texture* forage_texture = ResManager::GetInstance()->LoadTexture(_T("StardewValley_Forage"), _T("texture\\StardewValley_Forage.png"));
	Texture* crop_texture = ResManager::GetInstance()->LoadTexture(_T("StardewValley_Crop"), _T("texture\\StardewValley_Crop.png"));
	ItemSprite* hoe_sprite = DEBUG_NEW ItemSprite();
	hoe_sprite->QuickSet(tool_texture, hoe, Vector2{ 0, 32 }, Vector2{ 16, 16 });
	hoe->sprite_ = hoe_sprite;
	ItemSprite* watering_pot_sprite = DEBUG_NEW ItemSprite();
	watering_pot_sprite->QuickSet(tool_texture, watering_pot, Vector2{ 0, 608 }, Vector2{ 16, 16 });
	watering_pot->sprite_ = watering_pot_sprite;
	ItemSprite* pickaxe_sprite = DEBUG_NEW ItemSprite();
	pickaxe_sprite->QuickSet(tool_texture, pickaxe, Vector2{ 0, 224 }, Vector2{ 16, 16 });
	pickaxe->sprite_ = pickaxe_sprite;
	ItemSprite* axe_sprite = DEBUG_NEW ItemSprite();
	axe_sprite->set_texture(tool_texture);
	axe_sprite->set_base_pos(Vector2{ 0, 416 });
	axe_sprite->set_scale(Vector2{ 16, 16 });
	axe->sprite_ = axe_sprite;
	ItemSprite* stone_sprite = DEBUG_NEW ItemSprite();
	stone_sprite->set_texture(forage_texture);
	stone_sprite->set_base_pos(Vector2{ 136, 198 });
	stone_sprite->set_scale(Vector2{ 16, 16 });
	stone->sprite_ = stone_sprite;
	stone_sprite->set_owner(stone);
	ItemSprite* weed_sprite = DEBUG_NEW ItemSprite();
	weed_sprite->set_texture(forage_texture);
	weed_sprite->set_base_pos(Vector2{ 32, 192 });
	weed_sprite->set_scale(Vector2{ 32, 32 });
	weed->sprite_ = weed_sprite;
	weed_sprite->set_owner(weed);
	ItemSprite* wood_sprite = DEBUG_NEW ItemSprite();
	wood_sprite->set_texture(forage_texture);
	wood_sprite->set_base_pos(Vector2{ 70, 199 });
	wood_sprite->set_scale(Vector2{ 16, 16 });
	wood->sprite_ = wood_sprite;
	wood_sprite->set_owner(wood);
	ItemSprite* parsnip_seed_sprite = DEBUG_NEW ItemSprite();
	parsnip_seed_sprite->set_texture(crop_texture);
	parsnip_seed_sprite->set_base_pos(Vector2{ 0, 16 });
	parsnip_seed_sprite->set_scale(Vector2{ 16, 16 });
	parsnip_seed->sprite_ = parsnip_seed_sprite;
	parsnip_seed_sprite->set_owner(parsnip_seed);
	ItemSprite* parsnip_seed_sprite0 = DEBUG_NEW ItemSprite();
	parsnip_seed_sprite0->set_texture(crop_texture);
	parsnip_seed_sprite0->set_base_pos(Vector2{ 0, 16 });
	parsnip_seed_sprite0->set_scale(Vector2{ 16, 16 });
	parsnip_seed_sprite0->set_owner(parsnip_seed);
	ItemSprite* parsnip_seed_sprite1 = DEBUG_NEW ItemSprite();
	parsnip_seed_sprite1->set_texture(crop_texture);
	parsnip_seed_sprite1->set_base_pos(Vector2{ 16, 16 });
	parsnip_seed_sprite1->set_scale(Vector2{ 16, 16 });
	parsnip_seed_sprite1->set_owner(parsnip_seed);
	ItemSprite* parsnip_seed_sprite2 = DEBUG_NEW ItemSprite();
	parsnip_seed_sprite2->set_texture(crop_texture);
	parsnip_seed_sprite2->set_base_pos(Vector2{ 32, 16 });
	parsnip_seed_sprite2->set_scale(Vector2{ 16, 16 });
	parsnip_seed_sprite2->set_owner(parsnip_seed);
	ItemSprite* parsnip_seed_sprite3 = DEBUG_NEW ItemSprite();
	parsnip_seed_sprite3->set_texture(crop_texture);
	parsnip_seed_sprite3->set_base_pos(Vector2{ 48, 16 });
	parsnip_seed_sprite3->set_scale(Vector2{ 16, 16 });
	parsnip_seed_sprite3->set_owner(parsnip_seed);
	ItemSprite* parsnip_seed_sprite4 = DEBUG_NEW ItemSprite();
	parsnip_seed_sprite4->set_texture(crop_texture);
	parsnip_seed_sprite4->set_base_pos(Vector2{ 64, 16 });
	parsnip_seed_sprite4->set_scale(Vector2{ 16, 16 });
	parsnip_seed_sprite4->set_owner(parsnip_seed);
	ItemSprite* parsnip_seed_sprite5 = DEBUG_NEW ItemSprite();
	parsnip_seed_sprite5->set_texture(crop_texture);
	parsnip_seed_sprite5->set_base_pos(Vector2{ 80, 16 });
	parsnip_seed_sprite5->set_scale(Vector2{ 16, 16 });
	parsnip_seed_sprite5->set_owner(parsnip_seed);
	parsnip_seed->set_level_sprite(0, parsnip_seed_sprite0);
	parsnip_seed->set_level_sprite(1, parsnip_seed_sprite1);
	parsnip_seed->set_level_sprite(2, parsnip_seed_sprite2);
	parsnip_seed->set_level_sprite(3, parsnip_seed_sprite3);
	parsnip_seed->set_level_sprite(4, parsnip_seed_sprite4);
	parsnip_seed->set_level_sprite(5, parsnip_seed_sprite5);
	ItemSprite* parsnip_sprite = DEBUG_NEW ItemSprite();
	parsnip_sprite->set_texture(crop_texture);
	parsnip_sprite->set_base_pos(Vector2{ 96, 16 });
	parsnip_sprite->set_scale(Vector2{ 16, 16 });
	parsnip_sprite->set_owner(parsnip);
	parsnip->sprite_ = parsnip_sprite;



	ItemAnimator* hoe_animator = new ItemAnimator();
	hoe_animator->CreateAnimation(_T("Use_Hoe_Front"), tool_texture, Vector2{64, 32}, Vector2{64, 64}
	, Vector2{64, 0}, Vector2{0, 0}, .1f, 5, false, RENDER_LAYER::PLAYER);
	hoe_animator->CreateAnimation(_T("Use_Hoe_Back"), tool_texture, Vector2{ 64, 160 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::DEFAULT);
	hoe_animator->CreateAnimation(_T("Use_Hoe_Right"), tool_texture, Vector2{ 64, 96 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	hoe_animator->CreateAnimation(_T("Use_Hoe_Left"), tool_texture, Vector2{ 64, 96 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	hoe->animator_ = hoe_animator;

	ItemAnimator* watering_pot_animator = new ItemAnimator();
	watering_pot_animator->CreateAnimation(_T("Use_WateringPot_Front"), tool_texture, Vector2{ 64, 608 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	watering_pot_animator->CreateAnimation(_T("Use_WateringPot_Back"), tool_texture, Vector2{ 64, 736 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::DEFAULT);
	watering_pot_animator->CreateAnimation(_T("Use_WateringPot_Right"), tool_texture, Vector2{ 64, 672 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	watering_pot_animator->CreateAnimation(_T("Use_WateringPot_Left"), tool_texture, Vector2{ 64, 672 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	watering_pot->animator_ = watering_pot_animator;

	ItemAnimator* pickaxe_animator = new ItemAnimator();
	pickaxe_animator->CreateAnimation(_T("Use_Pickaxe_Front"), tool_texture, Vector2{ 64, 224 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	pickaxe_animator->CreateAnimation(_T("Use_Pickaxe_Back"), tool_texture, Vector2{ 64, 352 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::DEFAULT);
	pickaxe_animator->CreateAnimation(_T("Use_Pickaxe_Right"), tool_texture, Vector2{ 64, 288 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	pickaxe_animator->CreateAnimation(_T("Use_Pickaxe_Left"), tool_texture, Vector2{ 64, 288 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	pickaxe->animator_ = pickaxe_animator;

	ItemAnimator* axe_animator = new ItemAnimator();
	axe_animator->CreateAnimation(_T("Use_Axe_Front"), tool_texture, Vector2{ 64, 416 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	axe_animator->CreateAnimation(_T("Use_Axe_Back"), tool_texture, Vector2{ 64, 544 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::DEFAULT);
	axe_animator->CreateAnimation(_T("Use_Axe_Right"), tool_texture, Vector2{ 64, 480 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	axe_animator->CreateAnimation(_T("Use_Axe_Left"), tool_texture, Vector2{ 64, 480 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	axe->animator_ = axe_animator;


	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::HOE,				static_cast<IItem*>(hoe)));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WATERING_POT,		static_cast<IItem*>(watering_pot)));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PICKAXE,			static_cast<IItem*>(pickaxe)));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::AXE,				static_cast<IItem*>(axe)));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::STONE,			static_cast<IItem*>(stone)));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WEED,				static_cast<IItem*>(weed)));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WOOD,				static_cast<IItem*>(wood)));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PARSNIP_SEED,		static_cast<IItem*>(parsnip_seed)));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PARSNIP,			static_cast<IItem*>(parsnip)));


}

const IItem* ItemDb::get_item(int item_code)
{
	auto it = items_.find(item_code);
	if (it != items_.end()) {
		return (it->second);
	}
	return nullptr;
}
