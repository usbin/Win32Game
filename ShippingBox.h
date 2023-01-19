#pragma once
#include "global.h"
#include "RealObject.h"
class ItemData;
/// <summary>
/// ���ϻ���
/// </summary>
class ShippingBox : public RealObject
{
private:
	std::vector<const ItemData*>items_;
public:
	void Init();
	virtual void CreateInteractor() override;
	// RealObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnInteract(const GObject* req_obj) override;
	UINT CellItems();	//���� �������� ������ ����ؼ� �����ϰ� ������ ����
};

