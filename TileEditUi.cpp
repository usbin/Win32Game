#include "TileEditUi.h"
#include "PanelUi.h"
#include "ButtonUi.h"
#include "Texture.h"
#include "Sprite.h"
#include "TileUi.h"
#include "Director_Scene_Tool.h"
#include "Tile.h"


#define TILE_UI_BASE_POS_X 5
#define TILE_UI_BASE_POS_Y 50
#define TILE_UI_SCALE_X 32
#define TILE_UI_SCALE_Y 32

TileEditUi::TileEditUi()
	:PanelUi()
	, page_(0)
{
}

TileEditUi::~TileEditUi()
{
	SafeDeleteVector<Ui*>(get_children_unsafe());
	SafeDeleteVector<Sprite*>(tile_ui_sprites_);
}

void TileEditUi::CreateExitBtn()
{
	ButtonUi* exit_btn = new ButtonUi(true);
	exit_btn->set_pos(Vector2{ get_scale().x - 25.f, 5.f });
	exit_btn->set_scale(Vector2{ 20, 20 });
	exit_btn->set_group_type(GROUP_TYPE::UI);
	exit_btn->set_name(_T("Exit Button"));
	Texture* exit_texture = ResManager::GetInstance()->LoadTexture(_T("Exit Button"), _T("texture\\Exit_Btn.bmp"));
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
	add_btn->set_pos(Vector2{ 0, 25 });
	add_btn->set_scale(Vector2{ 20, 20 });
	add_btn->set_group_type(GROUP_TYPE::UI);
	add_btn->set_name(_T("Add Button"));
	Texture* add_texture = ResManager::GetInstance()->LoadTexture(_T("Add Button"), _T("texture\\plus-btn.bmp"));
	Sprite* add_sprite = new Sprite();
	add_sprite->QuickSet(add_texture, add_btn, 0, 0, 1, 1);
	add_btn->ChangeSprite(add_sprite);
	add_btn->set_parent(this);
	this->AddChild(add_btn);
	//이벤트 등록
	add_btn->AddOnClickHandler([](DWORD_PTR window, DWORD_PTR _director) {
		TileEditUi* tile_edit_window = reinterpret_cast<TileEditUi*>(window);
		if (tile_edit_window != nullptr) {
			Director_Scene_Tool* director = reinterpret_cast<Director_Scene_Tool*>(_director);
			if (director != nullptr) {
				director->ChangeMode(TILE_EDIT_MODE::ADD);
			}
		}
		}, reinterpret_cast<DWORD_PTR>(this), reinterpret_cast<DWORD_PTR>(director_));
	mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::ADD)] = add_btn;
}

void TileEditUi::CreateColliderModeBtn()
{
	ButtonUi* collider_btn = new ButtonUi(true);
	collider_btn->set_pos(Vector2{ 25, 25 });
	collider_btn->set_scale(Vector2{ 20, 20 });
	collider_btn->set_group_type(GROUP_TYPE::UI);
	collider_btn->set_name(_T("Collider Button"));
	Texture* collider_texture = ResManager::GetInstance()->LoadTexture(_T("Collider Button"), _T("texture\\collider-btn.bmp"));
	Sprite* collider_sprite = new Sprite();
	collider_sprite->QuickSet(collider_texture, collider_btn, 0, 0, 1, 1);
	collider_btn->ChangeSprite(collider_sprite);
	collider_btn->set_parent(this);
	this->AddChild(collider_btn);
	//이벤트 등록
	collider_btn->AddOnClickHandler([](DWORD_PTR window, DWORD_PTR _director) {
		TileEditUi* tile_edit_window = reinterpret_cast<TileEditUi*>(window);
		if (tile_edit_window != nullptr) {
			Director_Scene_Tool* director = reinterpret_cast<Director_Scene_Tool*>(_director);
			if (director != nullptr) {
				director->ChangeMode(TILE_EDIT_MODE::EDIT_COLLIDER);
			}
		}
		}, reinterpret_cast<DWORD_PTR>(this), reinterpret_cast<DWORD_PTR>(director_));
	mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::EDIT_COLLIDER)] = collider_btn;
}

void TileEditUi::CreateArrowBtns()
{
	ButtonUi* left_arrow_btn = new ButtonUi(true);
	left_arrow_btn->set_pos(Vector2{ -50.f, get_final_pos().y + get_scale().y - 40.f });
	left_arrow_btn->set_scale(Vector2{ 40, 40 });
	left_arrow_btn->set_group_type(GROUP_TYPE::UI);
	left_arrow_btn->set_name(_T("Left Arrow Button"));
	Texture* left_arrow_texture = ResManager::GetInstance()->LoadTexture(_T("Left Arrow Button"), _T("texture\\left-arrow-btn.bmp"));
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
	Texture* right_arrow_texture = ResManager::GetInstance()->LoadTexture(_T("Right Arrow Button"), _T("texture\\right-arrow-btn.bmp"));
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

	int max_row = (get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X;
	int max_col = (get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y;
	for (UINT i = 0; i < max_row * max_col; i++) {
		TileUi* tile_ui = new TileUi(true);
		tile_ui->set_group_type(GROUP_TYPE::UI);
		tile_ui->set_scale(Vector2{ TILE_UI_SCALE_X, TILE_UI_SCALE_Y });
		tile_ui->set_pos(Vector2{ TILE_UI_BASE_POS_X + (i % max_row) * (tile_ui->get_scale().x), TILE_UI_BASE_POS_Y + (i / max_row) * (tile_ui->get_scale().y) });
		tile_ui->set_name(_T(""));
		tile_ui->set_director(director_);
		tile_ui->set_parent(this);
		this->AddChild(tile_ui);
		tile_uis_.push_back(tile_ui);
	}
}

void TileEditUi::AddTileListFromTexture(Texture* texture, const Vector2& texture_base_pos, const Vector2& texture_scale, const Vector2& sprite_scale, const Vector2& interval, int count)
{
	int count_in_row_texture = texture_scale.x / sprite_scale.x;
	int max_row = (get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X;
	int max_col = (get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y;
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
	int max_row = (get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X;
	int max_col = (get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y;
	for (UINT tile_ui_i = 0; tile_ui_i < min((tile_ui_sprites_.size() - (page) * max_row * max_col), max_row * max_col); tile_ui_i++) {
		tile_uis_[tile_ui_i] ->ChangeSprite(new Sprite(*tile_ui_sprites_[page*max_col*max_row+tile_ui_i]));
		tile_ui_sprites_[page * max_col * max_row + tile_ui_i]->set_owner(tile_uis_[tile_ui_i]);
	}
	
	
}

void TileEditUi::ChangePage(UINT page)
{
	int max_row = (get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X;
	int max_col = (get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y;
	UINT max_page = tile_ui_sprites_.size()/(max_row * max_col);
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
	CreateColliderModeBtn();// 콜라이더 버튼
	
	
	//이 윈도우 위에 타일 Ui들 얹기
	//모든 타일 Ui에 대해서 클릭 이벤트 등록
	// - 타일Ui는 현재 모드를 TileEditUi로부터 가져와야 함.
	// - 타일Ui는 현재 모드에 따라 각각 동작 정의
	// - Add: 배치된 타일 드래그로 이동/타일Ui 윈도우에서 드래그해서 배치 가능
	// - Increase priority: 배치된 타일의 우선순위 올림. 최대값 존재.
	// - Decrease priority: 배치된 타일의 우선순위 내림. 최소 0.

	
	//타일셋은 texture에서 부분부분 불러옴.
	Texture* crop_texture = ResManager::GetInstance()->LoadTexture(_T("Harvest Moon Crops"), _T("texture\\Harvest-Moon_Crops.bmp"));

	Texture* farm_texture = ResManager::GetInstance()->LoadTexture(_T("Harvest Moon Farm"), _T("texture\\Harvest-Moon_Farm-Full.bmp"));

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

void TileEditUi::PickTileUi(TileUi* tile_ui)
{
	if (picked_tile_ui_ != nullptr) {
		picked_tile_ui_->Unpick();
	}
	tile_ui->Pick();
	picked_tile_ui_ = tile_ui;
}
