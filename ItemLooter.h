#pragma once
#include "global.h"

class Player;
class IItem;
/// <summary>
/// �ֺ��� ������ �������� �ڽſ��Է� ������.
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

