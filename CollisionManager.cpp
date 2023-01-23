#include "CollisionManager.h"
#include "GObject.h"
#include "RealObject.h"
#include "SceneManager.h"
#include "Collider.h"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::Init()
{
	//Player-Monster
	CheckGroupBitmap(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	//Missile-Monster
	CheckGroupBitmap(GROUP_TYPE::MISSILE, GROUP_TYPE::MONSTER);
	//Interactor-Interactor
	CheckGroupBitmap(GROUP_TYPE::INTERACTOR, GROUP_TYPE::INTERACTOR);

	CheckGroupBitmap(GROUP_TYPE::PLAYER, GROUP_TYPE::INVISIBLE_WALL);
	CheckGroupBitmap(GROUP_TYPE::PLAYER, GROUP_TYPE::SHIPPING_BOX);
}

void CollisionManager::Update()
{
	//현재 씬의 모든 오브젝트의 콜리더를 받아와야함.
	//(1)충돌 가능한 그룹의 비트맵 32x32 => Init에서 설정해줄것임.
	//(2)비트맵을 순회하며 현재 씬의 해당 그룹A, 그룹B 오브젝트 리스트를 받아옴.
	//(3)두 그룹의 충돌 상태 체크
	// - (i) 이전에 충돌하지 않았고 지금 충돌했음 -> OnCollisionEnter
	// - (ii) 이전에 충돌했고 지금도 충돌함 -> OnCollisionStay
	// - (iii) 이전에 충돌했고 지금은 충돌하지 않음 -> OnCollisionExit
	for (UINT i = 0; i < static_cast<UINT>(GROUP_TYPE::END); i++) {
		for (UINT j = i; j < static_cast<UINT>(GROUP_TYPE::END); j++) {
			// 두 그룹의 충돌여부가 체크돼있을 때에만 + 둘다 UI가 아닐 때에만
			if (static_cast<GROUP_TYPE>(i) != GROUP_TYPE::UI
				&& static_cast<GROUP_TYPE>(j) != GROUP_TYPE::UI
				&&
				group_collision_bitmap_[i] & (1 << j)) {
				const std::vector<GObject*>& group1_objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(static_cast<GROUP_TYPE>(i));
				const std::vector<GObject*>& group2_objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(static_cast<GROUP_TYPE>(j));
				GroupObjectCollision(group1_objs, group2_objs);
			}
			
		}
	}
	
}

void CollisionManager::CheckGroupBitmap(GROUP_TYPE group1, GROUP_TYPE group2)
{
	// 비트열에서 [0,1]과 [1,0]이 의미하는 건 같으므로(0번 그룹과 1번 그룹의 충돌여부)
	// 대각선 절반만 사용함.
	// 무조건 작은 그룹이 행으로 쓰이게 함. ( [0,1]만 사용하고 [1,0]은 사용하지 않음 )
	UINT row = static_cast<UINT>(group1);
	UINT col = static_cast<UINT>(group2);
	if (row > col) {
		col = static_cast<UINT>(group1);
		row = static_cast<UINT>(group2);
	}

	group_collision_bitmap_[row] |= 1 << col;

}

void CollisionManager::GroupObjectCollision(const std::vector<GObject*>& group1_objs, const std::vector<GObject*>& group2_objs)
{
	for (int i = 0; i < group1_objs.size(); i++) {
		RealObject* obj1 = static_cast<RealObject*>(group1_objs[i]);

		if (obj1->get_collider() == nullptr) continue; //하나라도 콜라이더가 없으면 충돌x

		for (int j = 0; j < group2_objs.size(); j++) {
			RealObject* obj2 = static_cast<RealObject*>(group2_objs[j]);
			
			if (obj2->get_collider() == nullptr) continue; //하나라도 콜라이더가 없으면 충돌x
			if (obj1 == obj2) continue; //동일 오브젝트끼리는 충돌x


			// 이전 충돌 여부로 분류해서 Collider 콜백함수 실행
			// 더 작은 값이 첫번째 아이디로 오도록
			UINT cid1 = obj1->get_collider()->get_id();
			UINT cid2 = obj2->get_collider()->get_id();
			if (cid1 > cid2) {
				cid1 = obj2->get_collider()->get_id();
				cid2 = obj1->get_collider()->get_id();
			}
			CollisionId cls_id;
			cls_id.collider1_id = cid1;
			cls_id.collider2_id = cid2;
			auto it = prev_collision_.find(cls_id.Id);

			if (it == prev_collision_.end()) {
				prev_collision_.insert(std::make_pair(cls_id.Id, false));
				it = prev_collision_.find(CollisionId{ cid1, cid2 }.Id);
			}

			//충돌일 경우
			if (IsCollision(obj1, obj2)) {

				//(1) FALSE임 -> 최초 충돌임.
				if (!it->second) {
					// 둘다 삭제 예정이 아닐 때에만
					if (!obj1->IsDead() && !obj2->IsDead()) {
						prev_collision_.insert(std::make_pair(cls_id.Id, true));
						obj1->get_collider()->OnCollisionEnter(obj2->get_collider());
						obj2->get_collider()->OnCollisionEnter(obj1->get_collider());

						it->second = true;
					}
					//하나라도 삭제 예정이면 아무 처리x
				}

				//(2) TRUE임 -> 충돌중임
				else{
					//둘다 삭제 예정이 아닐 때에만
					if (!obj1->IsDead() && !obj2->IsDead()) {
						obj1->get_collider()->OnCollisionStay(obj2->get_collider());
						obj2->get_collider()->OnCollisionStay(obj1->get_collider());

						it->second = true;
					}
					//하나라도 삭제 예정이면 자연스럽게 Exit 처리
					else {
						obj1->get_collider()->OnCollisionExit(obj2->get_collider());
						obj2->get_collider()->OnCollisionExit(obj1->get_collider());

						it->second = false;
					}

				}

			}
			//충돌이 아닐 경우
			else {
				//(3) TRUE임 -> 충돌에서 빠져나옴.
				if (it->second) {
					obj1->get_collider()->OnCollisionExit(obj2->get_collider());
					obj2->get_collider()->OnCollisionExit(obj1->get_collider());
				}
				it->second = false;
			}
		}
	}
}

bool CollisionManager::IsCollision(RealObject* obj1, RealObject* obj2)
{
	//충돌 여부: obj1과 obj2의 범위가 겹친다.
	// = x좌표간 거리가 둘의 가로 길이의 합의 절반보다 작고
	//	 y좌표간 거리가 둘의 세로 길이의 합의 절반보다 작다
	Collider* c1 = obj1->get_collider();
	Collider* c2 = obj2->get_collider();
	
	return
		abs(c1->get_pos().x - c2->get_pos().x) < ((c1->get_scale().x + c2->get_scale().x) / 2)
		&& abs(c1->get_pos().y - c2->get_pos().y) < ((c1->get_scale().y + c2->get_scale().y) / 2);
}

void CollisionManager::ResetGroupBitmap()
{
	memset(group_collision_bitmap_, 0, sizeof(group_collision_bitmap_));
}
