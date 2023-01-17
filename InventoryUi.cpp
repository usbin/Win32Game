#include "InventoryUi.h"
#include "Player.h"
#include "ImageUi.h"
#include "Decorator.h"
#include "Core.h"
#include "ButtonUi.h"
#include "ResManager.h"
#include "Texture.h"
#include "UiSprite.h"
#include "Game.h"
#include "InventoryCellUi.h"
#include "Inventory.h"
#include "ItemData.h"
#include "PlayerItemHolder.h"
#include "ItemSprite.h"
InventoryUi::InventoryUi()
	: Ui(true)
{
}
void InventoryUi::Init(Player* player)
{

	owner_ = player;
	Vector2 resolution = Core::GetInstance()->get_resolution();
	set_pos(Vector2::Zero());
	set_scale(resolution);

	//1.하위 Ui 생성해서 전체 구성하고
	Vector2 body_offset = Vector2{ 120, 120 };
	child_ui_frame_body_ = DEBUG_NEW Ui(true);
	child_ui_frame_body_->set_pos(body_offset);
	child_ui_frame_body_->set_scale(get_scale() - body_offset*2.f);
	child_ui_frame_body_->set_parent(this);
	child_ui_frame_body_->set_group_type(GROUP_TYPE::UI);
	AddChild(child_ui_frame_body_);

	ButtonUi* exit_btn = DEBUG_NEW ButtonUi(true);
	exit_btn->set_pos(Vector2{child_ui_frame_body_->get_scale().x + 10.f , -40.f });
	exit_btn->set_scale(Vector2{ 30, 30 });
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Exit Button"), _T("texture\\StardewValley_ExitBtn.png"));
	UiSprite* sprite = DEBUG_NEW UiSprite();
	sprite->QuickSet(texture, exit_btn, Vector2{ 0, 0 }, texture->get_size());
	exit_btn->ChangeSprite(sprite);
	exit_btn->set_group_type(GROUP_TYPE::UI);
	exit_btn->set_parent(child_ui_frame_body_);
	exit_btn->AddOnClickHandler([](DWORD_PTR p_owner, DWORD_PTR param2) {
		Player* player = reinterpret_cast<Player*>(p_owner);
		Game::GetInstance()->ToggleInventory(player);
	}, reinterpret_cast<DWORD_PTR>(owner_), 0);
	child_ui_frame_body_->AddChild(exit_btn);

	for (int i = 0; i < CELL_COUNT_INLINE; i++) {
		InventoryCellUi* cell_line1 = DEBUG_NEW InventoryCellUi(true);
		cell_line1->set_pos(Vector2{ cell_offset_.x + i*(cell_size_.x+cell_distance_), cell_offset_.y});
		cell_line1->set_scale(cell_size_);
		cell_line1->set_group_type(GROUP_TYPE::UI);
		cell_line1->set_parent(child_ui_frame_body_);
		child_ui_frame_body_->AddChild(cell_line1);
		cells_[i] = cell_line1;

		InventoryCellUi* cell_line2 = DEBUG_NEW InventoryCellUi(true);
		cell_line2->set_pos(Vector2{ cell_offset_.x + i * (cell_size_.x + cell_distance_), cell_offset_.y + cell_size_.y+ cell_distance_*3.f });
		cell_line2->set_scale(cell_size_);
		cell_line2->set_group_type(GROUP_TYPE::UI);
		cell_line2->set_parent(child_ui_frame_body_);
		child_ui_frame_body_->AddChild(cell_line2);
		cells_[i + CELL_COUNT_INLINE] = cell_line2;

		InventoryCellUi* cell_line3 = DEBUG_NEW InventoryCellUi(true);
		cell_line3->set_pos(Vector2{ cell_offset_.x + i * (cell_size_.x + cell_distance_), cell_offset_.y + cell_size_.y*2.f + cell_distance_*4.f });
		cell_line3->set_scale(cell_size_);
		cell_line3->set_group_type(GROUP_TYPE::UI);
		cell_line3->set_parent(child_ui_frame_body_);
		child_ui_frame_body_->AddChild(cell_line3);
		cells_[i + CELL_COUNT_INLINE * 2] = cell_line3;
	}


	//2.Inventory에서 데이터 불러와서 채우고
	Inventory* inventory = owner_->get_inventory();
	const std::vector<ItemData*>& items = inventory->GetItems();
	for (int i = 0; i < CELL_COUNT_MAX; i++) {
		cells_[i]->Init(this, i, items[i]);
	}

	//3.Inventory에 핸들러 등록
	OnInventoryDataChangedData handler;
	OnInventoryDataChangedArgs handler_args;
	handler_args.sender = reinterpret_cast<DWORD_PTR>(this);
	handler.args = handler_args;
	handler.handler = [](Inventory* inventory, int index, ItemData* new_data, OnInventoryDataChangedArgs args) {
		reinterpret_cast<InventoryUi*>(args.sender)->ReloadData(index, new_data);
	};
	inventory->AddHandler(handler.handler, handler_args);


}

void InventoryUi::ReloadData(int index, const ItemData* new_data)
{
	cells_[index]->Reset(new_data);
}

void InventoryUi::Update()
{
	Ui::Update();

	if (owner_ && owner_->IsDead()) owner_ = nullptr;
	if (child_ui_frame_body_ && child_ui_frame_body_->IsDead()) child_ui_frame_body_ = nullptr;

	////드래그 앤 드롭 기능 구현.
	//if (drag_start_cell_ && KEY_CHECK(KEY::LBUTTON, KEY_STATE::UP)) {
	//	drag_start_cell_ = nullptr;
	//}

	ChildrenUpdate();

}

void InventoryUi::Render(ID3D11Device* p_d3d_device)
{
	if (child_ui_frame_body_) {
		Decorator::GetInstance()->GetHorizontalSplitFrame()->Render(p_d3d_device, child_ui_frame_body_, RENDER_LAYER::PLAYER);

		Vector2 pos = !is_static_pos() ? WorldToRenderPos(child_ui_frame_body_->get_final_pos()) : child_ui_frame_body_->get_final_pos();
		//1번부터 12번까지 숫자 표시(현재 선택중인 셀은 빨간색)
		for (int i = 0; i < CELL_COUNT_INLINE; i++) {
			TCHAR num[3];
			if (i >= 0 && i <= 9) _stprintf_s(num, _T("%d"), i + 1);
			else if(i==10) _stprintf_s(num, _T("%s"), _T("-"));
			else if (i == 11) _stprintf_s(num, _T("%s"), _T("="));

			D2D1::ColorF font_color = dynamic_cast<PlayerItemHolder*>(owner_->get_item_holder())->GetHoldIndex() == i ? D2D1::ColorF::Red : D2D1::ColorF::Black;
			DrawFixedsizeText(p_d3d_device, pos + cell_offset_ + Vector2{ cell_size_.x/2.f - 7.5f, -15.f } + Vector2{ (cell_size_.x+cell_distance_) * i , 0.f }, Vector2{ 15, 15 }
				, num, _tcslen(num), _T("둥근모꼴"), 14
				, font_color, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL
				, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, RENDER_LAYER::PLAYER);
		}


		if (drag_start_cell_) {
			const IItem* item = drag_start_cell_->get_item_data()->item;
			Vector2 mouse_pos = WorldToRenderPos(GET_MOUSE_POS());
			Vector2 img_scale = item->get_sprite()->get_scale()*2.f;
			DrawTexture(p_d3d_device, mouse_pos - img_scale / 2.f, img_scale
				, item->get_sprite()->get_base_pos(), item->get_sprite()->get_scale(), item->get_sprite()->get_texture()
				, RENDER_LAYER::TOP);
		}
	}

	ChildrenRender(p_d3d_device);
}

void InventoryUi::SetDragStart(int index)
{
	if (index >=0 && index < CELL_COUNT_MAX) {
		if(cells_[index]->get_item_data())
			drag_start_cell_ = cells_[index];
	}
}

void InventoryUi::SetDragEnd(int index)
{
	if (index >= 0 && index < CELL_COUNT_MAX) {
		if (drag_start_cell_) {
			//서로 변경
			owner_->get_inventory()->ChangeItemPos(index, drag_start_cell_->get_index());
			/*const ItemData* tmp = drag_start_cell_->get_item_data();
			drag_start_cell_->Reset(cells_[index]->get_item_data());
			cells_[index]->Reset(tmp);*/
			drag_start_cell_ = nullptr;
		}
	}
}
