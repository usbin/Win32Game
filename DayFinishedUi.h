#pragma once
#include "global.h"
#include "Ui.h"
#include "DayFinishedDetailBtn.h"
#include "DayFinishedDetailImgUi.h"
#include "DayFinishedInfoContainerUi.h"
#include "DayFinishedDateUi.h"

/// <summary>
/// �Ϸ簡 ������ ������ ���� ȭ��.
/// </summary>
class DayFinishedUi : public Ui	
{
private:
	const int FARM = 0;
	const int FORAGE = 1;
	const int FISHING = 2;
	const int MINE = 3;
	const int ETC = 4;
	const int TOTAL = 5;
	std::vector<const ItemData*> items_[5]; //ī�װ��� ���ϵ� ������
	UINT gold_sums_[6] = { 0 };

	Ui* containters_[6] = {nullptr};
	DayFinishedInfoContainerUi* info_containers_[6] = {nullptr};
	DayFinishedDetailImgUi* detail_imgs_[5] = {nullptr};//"����"�� ok��ư�� ��������.
	DayFinishedDetailBtn* detail_btns_[5] = {nullptr};	
	ButtonUi* ok_btn_ = nullptr;


public:
	DayFinishedUi(bool is_static_pos) : Ui(is_static_pos) {};
	void Init();
	void Calculate();
	void CreateChildUis();
	void DayFinish();
	void Render(ID3D11Device* p_d3d_device) override;
};

