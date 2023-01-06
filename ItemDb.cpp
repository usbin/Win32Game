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
	parsnip_seed->Init((int)ITEM_CODE::PARSNIP_SEED, _T("¼ø¹« ¾¾¾Ñ"));
	parsnip->Init((int)ITEM_CODE::PARSNIP, _T("¼ø¹«"));
	hoe->set_scale(Vector2{ 192, 192 });
	watering_pot->set_scale(Vector2{ 192, 192 });
	pickaxe->set_scale(Vector2{ 192, 192 });
	axe->set_scale(Vector2{ 192, 192 });

	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("StardewValley_Tool"), _T("texture\\StardewValley_Tool.png"));
	ItemSprite* hoe_sprite = DEBUG_NEW ItemSprite();
	hoe_sprite->set_texture(texture);
	hoe_sprite->set_base_pos(Vector2{0, 32 });
	hoe_sprite->set_scale(Vector2{ 16, 16 });
	hoe->sprite_ = hoe_sprite;
	ItemSprite* watering_pot_sprite = DEBUG_NEW ItemSprite();
	watering_pot_sprite->set_texture(texture);
	watering_pot_sprite->set_base_pos(Vector2{ 0, 608 });
	watering_pot_sprite->set_scale(Vector2{ 16, 16 });
	watering_pot->sprite_ = watering_pot_sprite;
	ItemSprite* pickaxe_sprite = DEBUG_NEW ItemSprite();
	pickaxe_sprite->set_texture(texture);
	pickaxe_sprite->set_base_pos(Vector2{ 0, 224 });
	pickaxe_sprite->set_scale(Vector2{ 16, 16 });
	pickaxe->sprite_ = pickaxe_sprite;
	ItemSprite* axe_sprite = DEBUG_NEW ItemSprite();
	axe_sprite->set_texture(texture);
	axe_sprite->set_base_pos(Vector2{ 0, 416 });
	axe_sprite->set_scale(Vector2{ 16, 16 });
	axe->sprite_ = axe_sprite;


	ItemAnimator* hoe_animator = new ItemAnimator();
	hoe_animator->CreateAnimation(_T("Use_Hoe_Front"), texture, Vector2{64, 32}, Vector2{64, 64}
	, Vector2{64, 0}, Vector2{0, 0}, .1f, 5, false, RENDER_LAYER::PLAYER);
	hoe_animator->CreateAnimation(_T("Use_Hoe_Back"), texture, Vector2{ 64, 160 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::DEFAULT);
	hoe_animator->CreateAnimation(_T("Use_Hoe_Right"), texture, Vector2{ 64, 96 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	hoe_animator->CreateAnimation(_T("Use_Hoe_Left"), texture, Vector2{ 64, 96 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	hoe->animator_ = hoe_animator;

	ItemAnimator* pickaxe_animator = new ItemAnimator();
	pickaxe_animator->CreateAnimation(_T("Use_Pickaxe_Front"), texture, Vector2{ 64, 224 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	pickaxe_animator->CreateAnimation(_T("Use_Pickaxe_Back"), texture, Vector2{ 64, 352 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::DEFAULT);
	pickaxe_animator->CreateAnimation(_T("Use_Pickaxe_Right"), texture, Vector2{ 64, 288 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	pickaxe_animator->CreateAnimation(_T("Use_Pickaxe_Left"), texture, Vector2{ 64, 288 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	pickaxe->animator_ = pickaxe_animator;

	ItemAnimator* axe_animator = new ItemAnimator();
	axe_animator->CreateAnimation(_T("Use_Axe_Front"), texture, Vector2{ 64, 416 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	axe_animator->CreateAnimation(_T("Use_Axe_Back"), texture, Vector2{ 64, 544 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::DEFAULT);
	axe_animator->CreateAnimation(_T("Use_Axe_Right"), texture, Vector2{ 64, 480 }, Vector2{ 64, 64 }
	, Vector2{ 64, 0 }, Vector2{ 0, 0 }, .1f, 5, false, RENDER_LAYER::PLAYER);
	axe_animator->CreateAnimation(_T("Use_Axe_Left"), texture, Vector2{ 64, 480 }, Vector2{ 64, 64 }
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

const IItem* ItemDb::GetItem(int item_code)
{
	auto it = items_.find(item_code);
	if (it != items_.end()) {
		return (it->second);
	}
	return nullptr;
}
