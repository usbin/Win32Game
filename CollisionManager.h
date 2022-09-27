#pragma once
#include "global.h"
class GObject;
class RealObject;

//�� ������ �浹 üũ�� �ϴ� �浹 �Ŵ���
class CollisionManager
{
	SINGLETON(CollisionManager);
private:
	//���� 0���� 31����
	//�� �������� 0�� ��Ʈ. �� ������ 31�� ��Ʈ.
	UINT group_collision_bitmap_[static_cast<int>(GROUP_TYPE::END)] = {0};
	//���� ������ �浹 ����
	std::map<ULONGLONG, bool> prev_collision_;
public:
	void Init();
	void Update();
	void CheckGroupBitmap(GROUP_TYPE group1, GROUP_TYPE group2);
	void GroupObjectCollision(const std::vector<GObject*>& group1_objs, const std::vector<GObject*>& group2_objs);
	bool IsCollision(RealObject* obj1, RealObject* obj2);
	void ResetGroupBitmap(); //�浹 ���� ��Ʈ�� �ʱ�ȭ
};

