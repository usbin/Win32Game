#include "DayFinishedUi.h"
#include "Game.h"
#include "ButtonUi.h"
#include "ItemData.h"
#include "SceneManager.h"
#include "Player.h"
#include "ShippingBox.h"
#include "ItemData.h"
#include "IItem.h"
#include "Inventory.h"
void DayFinishedUi::Init()
{
	//1. 시간 멈추고, 컨트롤 프리징
	Game::GetInstance()->TimeFreeze();
	Game::GetInstance()->ControlFreeze();

	//2. 정산할 데이터 로드
	Calculate();//items_에 카테고리별로 출하된 아이템 들어가게 됨.

	//3. 정산 화면 생성하기
	CreateChildUis();

	//4. 프리징 해제
	Game::GetInstance()->TimeUnfreeze();
	Game::GetInstance()->ControlUnfreeze();
}

void DayFinishedUi::Calculate()
{

	// Ui에 표시할 데이터 먼저 계산해서 얻어오기
	// - 카테고리별로 출하상자에 들어있는 아이템 리스트 가져오기
	// - 카테고리별로 채우고 미리보기 이미지 채우고 버튼 동작 정의

	const std::vector<GObject*>& gobjs_player = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::PLAYER);
	if (!gobjs_player.empty()) {
		Player* player = dynamic_cast<Player*>(gobjs_player[0]);
		const std::vector<GObject*>& gobjs_shipping_box = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::SHIPPING_BOX);
		//모든 출하상자의 아이템 정산
		for (int i = 0; i < gobjs_shipping_box.size(); i++) {
			ShippingBox* shipping_box = dynamic_cast<ShippingBox*>(gobjs_shipping_box[i]);
			std::vector<const ItemData*> items = shipping_box->get_items();
			for (int i = 0; i < items.size(); i++) {
				switch ((ITEM_CODE)items[i]->item->get_item_code())
				{
				case ITEM_CODE::PARSNIP:
					items_[FARM].push_back(items[i]);
					gold_sums_[FARM] += items[i]->item->get_price() * items[i]->amount;
					break;
				case ITEM_CODE::WOOD:
				case ITEM_CODE::WEED:
					items_[FORAGE].push_back(items[i]);
					gold_sums_[FORAGE] += items[i]->item->get_price() * items[i]->amount;
					break;
				case ITEM_CODE::STONE:
					items_[MINE].push_back(items[i]);
					gold_sums_[MINE] += items[i]->item->get_price() * items[i]->amount;
					break;
				case ITEM_CODE::HOE:
				case ITEM_CODE::WATERING_POT:
				case ITEM_CODE::PICKAXE:
				case ITEM_CODE::AXE:
				case ITEM_CODE::PARSNIP_SEED:
					items_[ETC].push_back(items[i]);
					gold_sums_[ETC] += items[i]->item->get_price() * items[i]->amount;
					break;
				}
				gold_sums_[TOTAL] += items[i]->item->get_price() * items[i]->amount;
			}
		}
	}




}

void DayFinishedUi::CreateChildUis()
{


	// 날짜 표시 ex) 1년째, 봄의 1일째
	UINT pure_day = Game::GetInstance()-> get_day();
	UINT year = pure_day / (28 * 4);
	UINT season = (pure_day % (28 * 4)) / 28;
	UINT day = (pure_day % 28);

	DayFinishedDateUi* calander = DEBUG_NEW DayFinishedDateUi(true);
	calander->set_pos(Vector2{ 280, 40 });
	calander->set_scale(Vector2{ 400, 60 });
	calander->set_group_type(GROUP_TYPE::UI);
	calander->set_parent(this);
	calander->Init(year+1, season, day);
	AddChild(calander);

	// 정산 표시
	const Vector2 left_top = Vector2{ 180, 160 };
	const Vector2 cont_size{ 600, 90 };
	const Vector2 dist{ 0, 7 };

	for (int i = 0; i < 6; i++) {
		Ui* cont = DEBUG_NEW Ui(true);
		DayFinishedInfoContainerUi* info_container = DEBUG_NEW DayFinishedInfoContainerUi(true);

		
		cont->set_pos(left_top + Vector2{ 0.f, i*(cont_size.y + dist.y) });
		cont->set_scale(cont_size);
		cont->set_name(_T("정산화면 개별 컨테이너"));
		cont->set_group_type(GROUP_TYPE::UI);
		cont->set_parent(this);
		AddChild(cont);
		containters_[i] = cont;

		info_container->set_pos(Vector2::Zero());
		info_container->set_scale(cont->get_scale());
		info_container->set_name(_T("정산 화면 정보 컨테이너"));
		info_container->set_group_type(GROUP_TYPE::UI);
		info_container->set_parent(cont);
		cont->AddChild(info_container);
		info_containers_[i] = info_container;



		if (i < 5) {
			DayFinishedDetailImgUi* detail_img = DEBUG_NEW DayFinishedDetailImgUi(true);
			detail_img->set_pos(Vector2{ cont->get_scale().x, 5.f });
			detail_img->set_scale(Vector2{ 80.f, 80.f });
			detail_img->set_name(_T("정산 화면 미리보기 이미지"));
			detail_img->set_group_type(GROUP_TYPE::UI);
			detail_img->set_parent(cont);
			cont->AddChild(detail_img);
			detail_imgs_[i] = detail_img;

			DayFinishedDetailBtn* detail_btn = DEBUG_NEW DayFinishedDetailBtn(true);
			detail_btn->set_pos(detail_img->get_pos() + Vector2{ detail_img->get_scale().x, detail_img->get_scale().y / 2.f - 15.f });
			detail_btn->set_scale(Vector2{ 30, 30 });
			detail_btn->set_name(_T("정산 화면 미리보기 버튼"));
			detail_btn->set_parent(cont);
			cont->AddChild(detail_btn);
			detail_btns_[i] = detail_btn;
		}
		
	}
	
	info_containers_[FARM]->Init(_T("농사"), gold_sums_[FARM]);
	info_containers_[FORAGE]->Init(_T("채집"), gold_sums_[FORAGE]);
	info_containers_[FISHING]->Init(_T("낚시"), gold_sums_[FISHING]);
	info_containers_[MINE]->Init(_T("채광"), gold_sums_[MINE]);
	info_containers_[ETC]->Init(_T("기타"), gold_sums_[ETC]);
	info_containers_[TOTAL]->Init(_T("총합"), gold_sums_[TOTAL]);

	ok_btn_ = DEBUG_NEW ButtonUi(true);
	ok_btn_->set_pos(info_containers_[5]->get_pos() + Vector2{ info_containers_[5]->get_scale().x+20.f, 20.f });
	ok_btn_->set_scale(Vector2{ 40, 40 });
	ok_btn_->AddOnClickHandler([](DWORD_PTR param1, DWORD_PTR param2) {
		DayFinishedUi* ui = reinterpret_cast<DayFinishedUi*>(param1);
		ui->DayFinish();
		DeleteGObject(ui, GROUP_TYPE::UI);
		}, reinterpret_cast<DWORD_PTR>(this), 0);
	ok_btn_->set_parent(containters_[5]);
	containters_[5]->AddChild(ok_btn_);

}

void DayFinishedUi::DayFinish()
{
	
	Game::GetInstance()->FinishDay();

}
