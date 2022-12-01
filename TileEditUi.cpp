#include "TileEditUi.h"
#include "PanelUi.h"
#include "ButtonUi.h"
#include "Texture.h"
#include "Sprite.h"
#include "TileUi.h"
#include "Director_Scene_Tool.h"
#include "Tile.h"
#include "SceneManager.h"
#include "InvisibleWall.h"
#include "Collider.h"
#include "UiManager.h"
#include "InvisibleWallEditFrame.h"

#define TILE_UI_BASE_POS_X 5
#define TILE_UI_BASE_POS_Y 50
#define TILE_UI_SCALE_X 32
#define TILE_UI_SCALE_Y 32

TileEditUi::TileEditUi()
	:PanelUi()
	, page_(0)
	, mode_(TILE_EDIT_MODE::ADD)
	, director_(nullptr)
	, mode_buttons_{}
	, picked_tile_ui_(nullptr)
	, dragging_(false)
	, wall_edit_frames_{}
{
	std::vector<GObject*> walls = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
	for (int i = 0; i < walls.size(); i++) {
		InvisibleWallEditFrame* frame = new InvisibleWallEditFrame();
		frame->set_content(static_cast<InvisibleWall*>(walls[i]));
		frame->set_name(_T("Invisible Wall Frame"));
		frame->set_group_type(GROUP_TYPE::UI);
		frame->set_is_selectable(true);
		CreateGObject(frame, GROUP_TYPE::UI);
		wall_edit_frames_.push_back(frame);
	}
}

TileEditUi::~TileEditUi()
{
	UiManager::GetInstance()->ResetSelection();
	SafeDeleteVector<Sprite*>(tile_ui_sprites_);
	for (int i = 0; i < wall_edit_frames_.size(); i++) {
		DeleteGObject(wall_edit_frames_[i], GROUP_TYPE::UI);
	}
	wall_edit_frames_.clear();
}

void TileEditUi::CreateExitBtn()
{
	ButtonUi* exit_btn = new ButtonUi(true);
	exit_btn->set_pos(Vector2{ get_scale().x - 25.f, 5.f });
	exit_btn->set_scale(Vector2{ 20, 20 });
	exit_btn->set_group_type(GROUP_TYPE::UI);
	exit_btn->set_name(_T("Exit Button"));
	Texture* exit_texture = ResManager::GetInstance()->LoadTexture(_T("Exit Button"), _T("texture\\Exit_Btn.png"));
	Sprite* sprite = new Sprite();
	sprite->QuickSet(exit_texture, exit_btn, 0, 0, 1, 1);
	exit_btn->ChangeSprite(sprite);
	exit_btn->set_parent(this);
	this->AddChild(exit_btn);
	//이벤트 등록
	exit_btn->AddOnClickHandler([](DWORD_PTR param1, DWORD_PTR param2) {
		//클릭하면 이 오브젝트 삭제
		DeleteGObject(reinterpret_cast<GObject*>(param1), GROUP_TYPE::UI);
		}, reinterpret_cast<DWORD_PTR>(this), 0);

}

void TileEditUi::CreateAddModeBtn()
{
	ButtonUi* add_btn = new ButtonUi(true);
	add_btn->set_scale(Vector2{ 20, 20 });
	add_btn->set_group_type(GROUP_TYPE::UI);
	add_btn->set_name(_T("Add Button"));
	Texture* add_texture = ResManager::GetInstance()->LoadTexture(_T("Add Button"), _T("texture\\plus-btn.png"));
	Sprite* add_sprite = new Sprite();
	add_sprite->QuickSet(add_texture, add_btn, 0, 0, 1, 1);
	add_btn->ChangeSprite(add_sprite);
	add_btn->set_parent(this);
	this->AddChild(add_btn);
	//이벤트 등록
	add_btn->AddOnClickHandler([](DWORD_PTR window, DWORD_PTR _director) {
		TileEditUi* tile_edit_window = reinterpret_cast<TileEditUi*>(window);
		if (tile_edit_window != nullptr) {
			tile_edit_window->ChangeMode(TILE_EDIT_MODE::ADD);
		}
		}, reinterpret_cast<DWORD_PTR>(this), reinterpret_cast<DWORD_PTR>(director_));
	mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::ADD)] = add_btn;
}

void TileEditUi::CreateRemoveModeBtn()
{
	ButtonUi* remove_btn = new ButtonUi(true);
	remove_btn->set_scale(Vector2{ 20, 20 });
	remove_btn->set_group_type(GROUP_TYPE::UI);
	remove_btn->set_name(_T("Remove Button"));
	Texture* remove_texture = ResManager::GetInstance()->LoadTexture(_T("Remove Button"), _T("texture\\minus-btn.png"));
	Sprite* remove_sprite = new Sprite();
	remove_sprite->QuickSet(remove_texture, remove_btn, 0, 0, 1, 1);
	remove_btn->ChangeSprite(remove_sprite);
	remove_btn->set_parent(this);
	this->AddChild(remove_btn);
	//이벤트 등록
	remove_btn->AddOnClickHandler([](DWORD_PTR window, DWORD_PTR _director) {
		TileEditUi* tile_edit_window = reinterpret_cast<TileEditUi*>(window);
		if (tile_edit_window != nullptr) {
			tile_edit_window->ChangeMode(TILE_EDIT_MODE::REMOVE);
		}
		}, reinterpret_cast<DWORD_PTR>(this), reinterpret_cast<DWORD_PTR>(director_));
	mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::REMOVE)] = remove_btn;
}

void TileEditUi::CreateColliderModeBtn()
{
	ButtonUi* collider_btn = new ButtonUi(true);
	collider_btn->set_scale(Vector2{ 20, 20 });
	collider_btn->set_group_type(GROUP_TYPE::UI);
	collider_btn->set_name(_T("Collider Button"));
	Texture* collider_texture = ResManager::GetInstance()->LoadTexture(_T("Collider Button"), _T("texture\\collider-btn.png"));
	Sprite* collider_sprite = new Sprite();
	collider_sprite->QuickSet(collider_texture, collider_btn, 0, 0, 1, 1);
	collider_btn->ChangeSprite(collider_sprite);
	collider_btn->set_parent(this);
	this->AddChild(collider_btn);
	//이벤트 등록
	collider_btn->AddOnClickHandler([](DWORD_PTR window, DWORD_PTR _director) {
		TileEditUi* tile_edit_window = reinterpret_cast<TileEditUi*>(window);
		if (tile_edit_window != nullptr) {
			tile_edit_window->ChangeMode(TILE_EDIT_MODE::EDIT_COLLIDER);
		}
		}, reinterpret_cast<DWORD_PTR>(this), reinterpret_cast<DWORD_PTR>(director_));
	mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::EDIT_COLLIDER)] = collider_btn;
}

void TileEditUi::CreateColliderDeleteModeBtn() {
	ButtonUi* collider_delete_btn = new ButtonUi(true);
	collider_delete_btn->set_scale(Vector2{ 20,20 });
	collider_delete_btn->set_group_type(GROUP_TYPE::UI);
	collider_delete_btn->set_name(_T("Collider Delete Button"));
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Collider Delete Button"), _T("texture\\collider-delete-btn.png"));
	Sprite* sprite = new Sprite();
	sprite->QuickSet(texture, collider_delete_btn, 0, 0, 1, 1);
	collider_delete_btn->ChangeSprite(sprite);
	collider_delete_btn->set_parent(this);
	this->AddChild(collider_delete_btn);
	collider_delete_btn->AddOnClickHandler([](DWORD_PTR window, DWORD_PTR _director) {
		TileEditUi* tile_edit_window = reinterpret_cast<TileEditUi*>(window);
		if (tile_edit_window != nullptr) {
			tile_edit_window->ChangeMode(TILE_EDIT_MODE::DELETE_COLLIDER);
		}
		}, reinterpret_cast<DWORD_PTR>(this), reinterpret_cast<DWORD_PTR>(director_));
	mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::DELETE_COLLIDER)] = collider_delete_btn;
}

void TileEditUi::CreateArrowBtns()
{
	ButtonUi* left_arrow_btn = new ButtonUi(true);
	left_arrow_btn->set_pos(Vector2{ -50.f, get_final_pos().y + get_scale().y - 40.f });
	left_arrow_btn->set_scale(Vector2{ 40, 40 });
	left_arrow_btn->set_group_type(GROUP_TYPE::UI);
	left_arrow_btn->set_name(_T("Left Arrow Button"));
	Texture* left_arrow_texture = ResManager::GetInstance()->LoadTexture(_T("Left Arrow Button"), _T("texture\\left-arrow-btn.png"));
	Sprite* left_arrow_sprite = new Sprite();
	left_arrow_sprite->QuickSet(left_arrow_texture, left_arrow_btn, 0, 0, 1, 1);
	left_arrow_btn->ChangeSprite(left_arrow_sprite);
	left_arrow_btn->set_parent(this);
	this->AddChild(left_arrow_btn);
	//이벤트 등록
	left_arrow_btn->AddOnClickHandler([](DWORD_PTR window, DWORD_PTR _) {
		TileEditUi* teu = reinterpret_cast<TileEditUi*>(window);
		teu->ChangePage(teu->get_page() - 1);
		}, reinterpret_cast<DWORD_PTR>(this), 0);

	ButtonUi* right_arrow_btn = new ButtonUi(true);
	right_arrow_btn->set_pos(Vector2{ 10.f+get_scale().x, get_final_pos().y + get_scale().y - 40.f });
	right_arrow_btn->set_scale(Vector2{ 40, 40 });
	right_arrow_btn->set_group_type(GROUP_TYPE::UI);
	right_arrow_btn->set_name(_T("Right Arrow Button"));
	Texture* right_arrow_texture = ResManager::GetInstance()->LoadTexture(_T("Right Arrow Button"), _T("texture\\right-arrow-btn.png"));
	Sprite* right_arrow_sprite = new Sprite();
	right_arrow_sprite->QuickSet(right_arrow_texture, right_arrow_btn, 0, 0, 1, 1);
	right_arrow_btn->ChangeSprite(right_arrow_sprite);
	right_arrow_btn->set_parent(this);
	this->AddChild(right_arrow_btn);
	//이벤트 등록
	right_arrow_btn->AddOnClickHandler([](DWORD_PTR window, DWORD_PTR _) {
		TileEditUi* teu = reinterpret_cast<TileEditUi*>(window);
		teu->ChangePage(teu->get_page() + 1);
		}, reinterpret_cast<DWORD_PTR>(this), 0);

}

void TileEditUi::CreateEmptyTileUis()
{

	int max_row = static_cast<int>((get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X);
	int max_col = static_cast<int>((get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y);
	for (UINT i = 0; i < static_cast<UINT>(max_row * max_col); i++) {
		TileUi* tile_ui = new TileUi(true);
		tile_ui->set_group_type(GROUP_TYPE::UI);
		tile_ui->set_scale(Vector2{ TILE_UI_SCALE_X, TILE_UI_SCALE_Y });
		tile_ui->set_pos(Vector2{ TILE_UI_BASE_POS_X + (i % max_row) * (tile_ui->get_scale().x), TILE_UI_BASE_POS_Y + (i / max_row) * (tile_ui->get_scale().y) });
		tile_ui->set_name(_T(""));
		tile_ui->set_director(director_);
		tile_ui->set_parent(this);
		this->AddChild(tile_ui);
		tile_ui->AddOnClickHandler([](DWORD_PTR tile_editor_p, DWORD_PTR tile_ui_idx_p) {
			TileEditUi* tile_edit_ui = reinterpret_cast<TileEditUi*>(tile_editor_p);
			int tile_ui_idx = static_cast<int>(tile_ui_idx_p);
			if(tile_edit_ui->get_mode() == TILE_EDIT_MODE::ADD)
				tile_edit_ui->PickTileUi(tile_ui_idx);
			}, reinterpret_cast<DWORD_PTR>(this), static_cast<DWORD_PTR>(i));
		tile_uis_.push_back(tile_ui);
	}
}

void TileEditUi::AddTileListFromTexture(Texture* texture, const Vector2& texture_base_pos, const Vector2& texture_scale, const Vector2& sprite_scale, const Vector2& interval, int count)
{
	int count_in_row_texture = static_cast<int>(texture_scale.x / sprite_scale.x);
	int max_row = static_cast<int>((get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X);
	int max_col = static_cast<int>((get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y);
	for (int i = 0; i < count; i++) {
		Sprite* sprite = new Sprite();
		sprite->QuickSet(texture
			, nullptr
			, texture_base_pos + Vector2{ (i % count_in_row_texture) * (sprite_scale.x + interval.x), i / count_in_row_texture * (sprite_scale.y + interval.y) }
		, sprite_scale);
		tile_ui_sprites_.push_back(sprite);
	}
}

void TileEditUi::LoadTileListFromTexture(UINT page)
{
	//n page에 올라가는 타일 수는
	// MIN(max_row * max_col, (전체타일ui수 - (page)*(max_row *max_col)))
	// 
	int max_row = static_cast<int>((get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X);
	int max_col = static_cast<int>((get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y);
	for (UINT tile_ui_i = 0; tile_ui_i < min((tile_ui_sprites_.size() - page * max_row * max_col), max_row * max_col); tile_ui_i++) {
		tile_uis_[tile_ui_i] ->ChangeSprite(new Sprite(*tile_ui_sprites_[page*max_col*max_row+tile_ui_i]));
		tile_ui_sprites_[page * max_col * max_row + tile_ui_i]->set_owner(tile_uis_[tile_ui_i]);
	}
	
	
}

void TileEditUi::ChangePage(UINT page)
{
	int max_row = static_cast<int>((get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X);
	int max_col = static_cast<int>((get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y);
	UINT max_page = static_cast<UINT>(tile_ui_sprites_.size()/(max_row * max_col));
	if (page < 0 || page > (max_page)) return;
	page_ = page;
	LoadTileListFromTexture(page);
}

void TileEditUi::Init()
{
	//상단 우측 닫기 버튼
	CreateExitBtn();

	// 모드 버튼들: 클릭됨/클릭되지 않음에 따라 다른 모습으로 구분되게 보여줘야함.
	CreateAddModeBtn(); //추가 버튼
	CreateRemoveModeBtn(); //삭제 버튼
	CreateColliderModeBtn();// 콜라이더 버튼
	CreateColliderDeleteModeBtn(); //콜라이더 삭제 버튼
	int pos_idx = 0;
	for (int i = 0; i < static_cast<int>(TILE_EDIT_MODE::END); i++) {
		if (mode_buttons_[i]) {
			mode_buttons_[i]->set_pos(Vector2{ pos_idx++ * 25, 25 });
		}
	}
	mode_buttons_[0]->set_selected(true);
	
	//이 윈도우 위에 타일 Ui들 얹기
	//모든 타일 Ui에 대해서 클릭 이벤트 등록
	// - 타일Ui는 현재 모드를 TileEditUi로부터 가져와야 함.
	// - 타일Ui는 현재 모드에 따라 각각 동작 정의
	// - Add: 배치된 타일 드래그로 이동/타일Ui 윈도우에서 드래그해서 배치 가능
	// - Increase priority: 배치된 타일의 우선순위 올림. 최대값 존재.
	// - Decrease priority: 배치된 타일의 우선순위 내림. 최소 0.
	
	//타일셋은 texture에서 부분부분 불러옴.
	Texture* crop_texture = ResManager::GetInstance()->LoadTexture(_T("Harvest Moon Crops"), _T("texture\\Harvest-Moon_Crops.png"));

	Texture* farm_texture = ResManager::GetInstance()->LoadTexture(_T("Harvest Moon Farm"), _T("texture\\Harvest-Moon_Farm-Full.png"));

	//빈 밭 sprite
	// - 범위 (32,41) ~(66, 57)
	// - 16x16
	// - 간격 2px, 0px
	// - 개수 2개	
	// - 한 행에 2개
	//AddTileListFromTexture(crop_texture, Vector2{ 32, 41 }, Vector2{ 66, 57 }, Vector2{ 16, 16 }, Vector2{ 2, 0 }, 2);
	//씨앗 심은 밭
	//AddTileListFromTexture(crop_texture, Vector2{ 99, 41 }, Vector2{ 133, 57 }, Vector2{ 16, 16 }, Vector2{ 2, 0 }, 2);
	//순무 성장과정
	//AddTileListFromTexture(crop_texture, Vector2{ 13, 135 }, Vector2{ 47, 187 }, Vector2{ 16, 16 }, Vector2{ 2, 2 }, 6);
	CreateEmptyTileUis();
	AddTileListFromTexture(farm_texture, Vector2{ 0, 0 }, Vector2{ 1024, 1024 }, Vector2{ 16, 16 }, Vector2{ 0, 0 }, (1024 * 1024)/(16*16));
	ChangePage(0);
	CreateArrowBtns();
}

void TileEditUi::Update()
{
	PanelUi::Update();

	switch (mode_) {
	case TILE_EDIT_MODE::ADD: {
		if (KEY_HOLD(KEY::LBUTTON)) {
			if (picked_tile_ui_) {
				Tile* tile = SceneManager::GetInstance()->get_current_scene()->GetTile(GET_MOUSE_POS());
				if (tile) tile->SetTile(picked_tile_ui_);
			}
		}
		if (KEY_DOWN(KEY::RBUTTON)) {
			picked_tile_ui_ = nullptr;
		}
	}
	break;
	case TILE_EDIT_MODE::REMOVE: {
		if (KEY_HOLD(KEY::LBUTTON)) {
			Tile* tile = SceneManager::GetInstance()->get_current_scene()->GetTile(GET_MOUSE_POS());
			if (tile) tile->ResetTile();
		}
	}

	break;
	case TILE_EDIT_MODE::EDIT_COLLIDER: {
		if (KEY_DOWN(KEY::LBUTTON) && UiManager::GetInstance()->focus_nothing()){
			dragging_ = true;
			drag_start_pos_ = GET_MOUSE_POS();
		}
		else if (KEY_HOLD(KEY::LBUTTON) && dragging_ && UiManager::GetInstance()->focus_nothing()) {
			prev_drag_pos_ = GET_MOUSE_POS();

		}
		else if (KEY_UP(KEY::LBUTTON) && dragging_) {
			//drag_start_pos_ <===> 현재 위치를 잇는 네모난 InvisibleWall 생성
			// 크기가 최소한 16x16일 때만 
			Vector2 drag_end_pos_ = GET_MOUSE_POS();
			Vector2 scale{ abs(drag_end_pos_.x - drag_start_pos_.x), abs(drag_end_pos_.y - drag_start_pos_.y) };
			if (scale.x >= 16.f && scale.y >= 16.f) {
				// InvisibleWall과 collider는 pos가 중앙, InvisibleWallFrame은 기준점이 좌상단임.
				InvisibleWall* wall = new InvisibleWall();
				wall->set_pos(Vector2{ min(drag_start_pos_.x+scale.x/2.f, drag_end_pos_.x+scale.x/2.f), min(drag_start_pos_.y+scale.y/2.f, drag_end_pos_.y+scale.y/2.f) });
				wall->set_scale(scale);
				wall->set_group_type(GROUP_TYPE::INVISIBLE_WALL);
				wall->set_name(_T("Invisible Wall"));
				CreateGObject(wall, GROUP_TYPE::INVISIBLE_WALL);

				Collider* collider = new Collider();
				collider->set_owner(wall);
				collider->set_scale(wall->get_scale());
				wall->set_collider(collider);

				InvisibleWallEditFrame* frame = new InvisibleWallEditFrame();
				frame->set_content(wall);
				frame->set_name(_T("Invisible Wall Frame"));
				frame->set_group_type(GROUP_TYPE::UI);
				frame->set_is_selectable(true);
				CreateGObject(frame, GROUP_TYPE::UI);
				wall_edit_frames_.push_back(frame);

			}
			dragging_ = false;

		}
	}
	break;
	case TILE_EDIT_MODE::DELETE_COLLIDER : {
		//클릭된 위치의 collider를 찾아서 삭제함.
		Ui* selected_ui = UiManager::GetInstance()->get_selected_target();
		InvisibleWallEditFrame* frame = dynamic_cast<InvisibleWallEditFrame*>(selected_ui);
		if (frame) {
			DeleteGObject(frame->get_content(), GROUP_TYPE::UI);
			frame->set_content(nullptr);
		}

	}
	break;
	}


	ChildrenUpdate();
}

void TileEditUi::Render(ID3D11Device* p_d3d_device)
{
	PanelUi::Render(p_d3d_device);
	ChildrenRender(p_d3d_device);
	/*switch (mode_) {
	case TILE_EDIT_MODE::ADD: {
		if (picked_tile_ui_) {
			Sprite* sprite = picked_tile_ui_->get_sprite();
			Vector2 tile_ui_scale = picked_tile_ui_->get_scale();
			Vector2 mouse_pos = WorldToRenderPos(GET_MOUSE_POS());
			TransparentBlt(hdc
				, static_cast<int>(mouse_pos.x - tile_ui_scale.x / 2.f)
				, static_cast<int>(mouse_pos.y - tile_ui_scale.y / 2.f)
				, static_cast<int>(tile_ui_scale.x)
				, static_cast<int>(tile_ui_scale.y)
				, sprite->get_texture()->get_hdc()
				, static_cast<int>(sprite->get_base_pos().x)
				, static_cast<int>(sprite->get_base_pos().y)
				, static_cast<int>(sprite->get_scale().x)
				, static_cast<int>(sprite->get_scale().y)
				, RGB(255, 0, 255));
		}
	}
	break;
	case TILE_EDIT_MODE::REMOVE: {
		Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Remove Button"), _T("texture\\minus-btn.bmp"));
		if (texture) {
			Vector2 mouse_pos = WorldToRenderPos(GET_MOUSE_POS());
			TransparentBlt(hdc
				, static_cast<int>(mouse_pos.x)
				, static_cast<int>(mouse_pos.y)
				, static_cast<int>(texture->get_width())
				, static_cast<int>(texture->get_height())
				, texture->get_hdc()
				, static_cast<int>(0)
				, static_cast<int>(0)
				, static_cast<int>(texture->get_width())
				, static_cast<int>(texture->get_height())
				, RGB(255, 0, 255));
		}
		
	}
	break;
	case TILE_EDIT_MODE::EDIT_COLLIDER: {
		if (KEY_HOLD(KEY::LBUTTON) && dragging_) {
			Vector2 start_pos = WorldToRenderPos(drag_start_pos_);
			Vector2 end_pos = WorldToRenderPos(prev_drag_pos_);
			SelectGdi _(hdc, PEN_TYPE::BLACK_DASH);
			SelectGdi __(hdc, BRUSH_TYPE::HOLLOW);
			Rectangle(hdc
				, static_cast<int>(start_pos.x)
				, static_cast<int>(start_pos.y)
				, static_cast<int>(end_pos.x)
				, static_cast<int>(end_pos.y));
			

		}
	}
	break;
	case TILE_EDIT_MODE::DELETE_COLLIDER: {
		Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Remove Button"), _T("texture\\minus-btn.bmp"));
		if (texture) {
			Vector2 mouse_pos = WorldToRenderPos(GET_MOUSE_POS());
			TransparentBlt(hdc
				, static_cast<int>(mouse_pos.x)
				, static_cast<int>(mouse_pos.y)
				, static_cast<int>(texture->get_width())
				, static_cast<int>(texture->get_height())
				, texture->get_hdc()
				, static_cast<int>(0)
				, static_cast<int>(0)
				, static_cast<int>(texture->get_width())
				, static_cast<int>(texture->get_height())
				, RGB(255, 0, 255));
		}
	}
	break;

	}*/
}

void TileEditUi::ChangeMode(TILE_EDIT_MODE mode)
{
	picked_tile_ui_ = nullptr;
	for (int i = 0; i < wall_edit_frames_.size(); i++) {
		wall_edit_frames_[i]->set_is_selectable(mode==TILE_EDIT_MODE::EDIT_COLLIDER||mode==TILE_EDIT_MODE::DELETE_COLLIDER);
	}
	UiManager::GetInstance()->ResetSelection();
	mode_buttons_[static_cast<ULONGLONG>(mode_)]->set_selected(false);
	mode_buttons_[static_cast<ULONGLONG>(mode)]->set_selected(true);
	mode_ = mode;
}

void TileEditUi::PickTileUi(int tile_ui_idx)
{
	if (tile_ui_idx < 0 || tile_ui_idx >= tile_uis_.size()) {
		return;
	}
	picked_tile_ui_ = tile_uis_[tile_ui_idx];
}
