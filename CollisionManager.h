#pragma once
#include "GObject.h"

//매 프레임 충돌 체크를 하는 충돌 매니저
class CollisionManager
{
	SINGLETON(CollisionManager);
private:
	//행은 0부터 31까지
	//맨 오른쪽이 0번 비트. 맨 왼쪽이 31번 비트.
	UINT group_collision_bitmap_[static_cast<int>(GROUP_TYPE::END)] = {0};
	//이전 프레임 충돌 여부
	std::map<ULONGLONG, bool> prev_collision_;
public:
	void Init();
	void Update();
	void CheckGroupBitmap(GROUP_TYPE group1, GROUP_TYPE group2);
	void GroupObjectCollision(const std::set<GObject*, GObjectPtCompare>& group1_objs, const std::set<GObject*, GObjectPtCompare>& group2_objs);
	bool IsCollision(GObject* obj1, GObject* obj2);
	void ResetGroupBitmap(); //충돌 관계 비트맵 초기화
};

