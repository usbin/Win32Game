#pragma once
#include "global.h"
#include "IItemHolder.h"
#include "IItem.h"
class Player;
class PlayerItemHolder : public IItemHolder
{
public:
	PlayerItemHolder();
	virtual ~PlayerItemHolder() override;

private:
	//홀더에 장착된 아이템
	const IItem* item_ = nullptr;
	Player* owner_ = nullptr;
public:
	

	virtual void set_owner(RealObject* owner) override { owner_ = static_cast<Player*>(owner); };
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override; //아이템 렌더링
	virtual void SetItem(const IItem* item) override;
};

