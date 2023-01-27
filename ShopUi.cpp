#include "ShopUi.h"
#include "Decorator.h"
#include "ButtonUi.h"
#include "Core.h"
#include "Player.h"
#include "ItemDb.h"
#include "Game.h"
ShopUi::~ShopUi()
{

	Game::GetInstance()->ControlUnfreeze();
}
void ShopUi::Init(const Player* player)
{
	set_pos(Vector2{ 200, 200 });
	set_scale(Vector2{ 600, 400 });
	

	Game::GetInstance()->ControlFreeze();
	//파는 아이템 리스트 초기화
	items_.push_back(ItemDb::GetInstance()->get_item((int)ITEM_CODE::PARSNIP_SEED));



	owner_ = player;

	item_cell_container_ = DEBUG_NEW Ui(true);
	item_cell_container_->set_pos(Vector2{ 0,0 });
	item_cell_container_->set_scale(Vector2{ get_scale().x, get_scale().y - 200 });
	item_cell_container_->set_group_type(GROUP_TYPE::UI);
	item_cell_container_->set_parent(this);
	AddChild(item_cell_container_);

	for (int i = 0; i < items_.size(); i++) {
		ShopItemCellUi* item_cell = DEBUG_NEW ShopItemCellUi(true);
		item_cell->set_pos(Vector2{ 12, 12 });
		item_cell->set_scale(Vector2{ get_scale().x - 12, 80.f });
		item_cell->set_group_type(GROUP_TYPE::UI);
		item_cell->set_parent(item_cell_container_);
		item_cell->Init(this, items_[i]);
		item_cell_container_->AddChild(item_cell);

		item_cells_.push_back(item_cell);

		gold_ui_ = DEBUG_NEW ShopGoldUi(true);
		gold_ui_->set_pos(Vector2{ 0.f, item_cell_container_->get_scale().y });
		gold_ui_->set_scale(Vector2{ 100.f, 40.f });
		gold_ui_->set_group_type(GROUP_TYPE::UI);
		gold_ui_->set_parent(this);
		gold_ui_->Init(this);
		AddChild(gold_ui_);

		//inventory_ui_ = DEBUG_NEW ShopInventoryUi(true);
		//inventory_ui_->set_pos(Vector2{ gold_ui_->get_scale().x, item_cell_container_->get_scale().y });
		//inventory_ui_->set_scale(Vector2{ Core::GetInstance()->get_resolution().x - gold_ui_->get_scale().x, Core::GetInstance()->get_resolution().y - item_cell_container_->get_scale().y });
		//inventory_ui_->set_group_type(GROUP_TYPE::UI);
		//inventory_ui_->set_parent(this);
		//inventory_ui_->Init(this);
		//AddChild(inventory_ui_);
	}

	

}

void ShopUi::Update()
{
	Ui::Update();


	if (KEY_DOWN(KEY::ESC)) {
		DeleteGObject(this, GROUP_TYPE::UI);
	}
}

void ShopUi::Render(ID3D11Device* p_d3d_device)
{
	if (item_cell_container_) {

		Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, item_cell_container_, RENDER_LAYER::PLAYER);
	}

	ChildrenRender(p_d3d_device);

}
