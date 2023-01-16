#pragma once
#include "global.h"

class Player;
class IItem;
/// <summary>
/// 주변에 떨어진 아이템을 자신에게로 끌어당김.
/// </summary>
class ItemLooter
{
private:
	Player* owner_ = nullptr;
	Vector2 pos_offset_{};
	const float LOOT_RANGE = 48.f;

public:
	void Init(Player* player, Vector2 offset);
	void Update();
	bool Loot(const IItem* item, UINT amount);
	inline Vector2 get_pos();
};

