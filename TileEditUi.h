#pragma once
#include "PanelUi.h"
#include "Texture.h"
class TileUi;
class Director_Scene_Tool;
class ButtonUi;
class Sprite;
class InvisibleWallEditFrame;




enum class TILE_EDIT_MODE {
	ADD,
	REMOVE,
	INCREASE_PRIORITY,
	DECREASE_PRIORITY,
	EDIT_COLLIDER,
	DELETE_COLLIDER,
	END
};
class TileEditUi : public PanelUi
{
public:
	TileEditUi();
	~TileEditUi();
private:
	Director_Scene_Tool* director_;

	ButtonUi* mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::END)];
	TILE_EDIT_MODE mode_;

	std::vector<TileUi*> tile_uis_;
	std::vector<Sprite*> tile_ui_sprites_;
	UINT page_;

	//==============
	//	ADD 모드
	//==============
	TileUi* picked_tile_ui_;

	//===============
	//	COLLIDER 모드
	//===============
	Vector2 drag_start_pos_;
	Vector2 prev_drag_pos_;
	bool dragging_;
	std::vector<InvisibleWallEditFrame*> wall_edit_frames_;

	//초기화
	void CreateExitBtn();
	void CreateAddModeBtn();
	void CreateRemoveModeBtn();
	void CreateColliderModeBtn();
	void CreateColliderDeleteModeBtn();
	void CreateArrowBtns();
	void CreateEmptyTileUis();
	void AddTileListFromTexture(Texture* texture, const Vector2& texture_base_pos, const Vector2& texture_scale
		, const Vector2& sprite_scale, const Vector2& interval, int count); //texture에서 TileUi들을 생성하고 tile_uis_에 추가


	void LoadTileListFromTexture(UINT page);//TileEditUi위에 TileUi를 실제로 얹는 작업
	void ChangePage(UINT page);
	void PickTileUi(int tile_ui_idx);

public:
	void Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void ChangeMode(TILE_EDIT_MODE mode);

	inline void set_director(Director_Scene_Tool* director) { director_ = director; };
	inline ButtonUi** get_mode_buttons() { return mode_buttons_; };
	inline TileUi* get_picked_tile_ui() { return picked_tile_ui_; };
	inline UINT get_page() { return page_; };
	inline TILE_EDIT_MODE get_mode() { return mode_; };
};

