#pragma once
#include "global.h"
#include "RealObject.h"
class ItemData;
/// <summary>
/// 출하상자
/// </summary>
class ShippingBox : public RealObject
{
private:
	std::vector<const ItemData*>items_;
public:
	~ShippingBox();
	void Init();
	virtual void CreateRenderCmp() override;
	virtual void CreateCollider() override;
	virtual void CreateInteractor() override;
	// RealObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnInteract(const GObject* req_obj) override;
	UINT CellItems();	//가진 아이템의 가격을 계산해서 리턴하고 아이템 비우기
	std::vector<const ItemData*>& get_items() { return items_; };
};

