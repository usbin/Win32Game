#pragma once
#include "GObject.h"

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
	void GroupObjectCollision(const std::set<GObject*, GObjectPtCompare>& group1_objs, const std::set<GObject*, GObjectPtCompare>& group2_objs);
	bool IsCollision(GObject* obj1, GObject* obj2);
	void ResetGroupBitmap(); //�浹 ���� ��Ʈ�� �ʱ�ȭ
};

