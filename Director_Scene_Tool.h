#pragma once
#include "global.h"
#include "RealObject.h"


class TileEditUi;
class ButtonUi;
class TileUi;
class TileCell;

enum class TILE_EDIT_MODE {
	ADD,
	INCREASE_PRIORITY,
	DECREASE_PRIORITY,
	EDIT_COLLIDER,
	END
};
class Director_Scene_Tool : public RealObject
{
public:
	Director_Scene_Tool();
	~Director_Scene_Tool();
private:
	TileEditUi* tile_edit_ui_;
	std::vector<TileCell*> tile_map_;
	TILE_EDIT_MODE mode_;

public:
	virtual void Update();


	inline TILE_EDIT_MODE get_mode() { return mode_; };
	void ChangeMode(TILE_EDIT_MODE mode);
	void CreateEmptyTilemap(const Vector2& tile_size, const Vector2& tile_count);
	void InsertTile(const Vector2& mouse_pos, TileUi* tile_ui); //mouse_pos 위치에 tile_ui에서 본뜬 tile 생성
};

