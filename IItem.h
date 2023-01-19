#pragma once
#include "global.h"
class RealObject;
class ItemSprite;
class IItemHolder;
/// <summary>
/// �����͸� �����ϱ� ���� ��ü�̹Ƿ� Init�� �����ϰ� ��� �Լ��� const���� ��.
/// </summary>
class IItem
{
public:
	virtual ~IItem() = 0 {};
	virtual void OnHold(RealObject* owner) const = 0;					//�������� ������� �� ����
	virtual int get_item_code() const = 0;
	virtual ItemSprite* get_sprite() const = 0;
	virtual ItemSprite* get_profile_sprite() const = 0;	//�κ��丮 ��� ���̴� sprite
	virtual void set_scale(Vector2 scale)  = 0;
	virtual Vector2 get_scale() const = 0;
	virtual UINT get_max_stack() const = 0;
	virtual UINT get_price() const = 0;
	virtual void UpdateOnHolder(IItemHolder* holder) const  = 0;
	virtual void RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const = 0;
};
