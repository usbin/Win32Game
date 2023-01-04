#pragma once
#include "PanelUi.h"
#include "Texture.h"
class TileUi;
class Director_Scene_Tool;
class ButtonUi;
class ISprite;
class InvisibleWallEditFrame;



#define TILE_UI_BASE_POS_X 5
#define TILE_UI_BASE_POS_Y 50
#define TILE_UI_SCALE_X 32
#define TILE_UI_SCALE_Y 32

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
	Director_Scene_Tool* director_ = nullptr;

	ButtonUi* mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::END)];
	ButtonUi* exit_button_ = nullptr;
	TILE_EDIT_MODE mode_;

	std::vector<TileUi*> tile_uis_;
	std::vector<GObjectSprite*> tile_ui_sprites_;
	UINT page_;

	//==============
	//	ADD ���
	//==============
	TileUi* picked_tile_ui_ = nullptr;

	//===============
	//	COLLIDER ���
	//===============
	Vector2 drag_start_pos_ = Vector2::Zero();
	Vector2 prev_drag_pos_ = Vector2::Zero();
	bool dragging_ = false;
	std::vector<InvisibleWallEditFrame*> wall_edit_frames_;

	//�ʱ�ȭ
	void CreateExitBtn();
	void CreateAddModeBtn();
	void CreateRemoveModeBtn();
	void CreateColliderModeBtn();
	void CreateColliderDeleteModeBtn();
	void CreateArrowBtns();
	void CreateEmptyTileUis(UINT row, UINT col);
	void AddTileListFromTexture(Texture* texture, const Vector2& texture_base_pos, const Vector2& texture_scale
		, const Vector2& sprite_scale, const Vector2& interval, int count); //texture���� TileUi���� �����ϰ� tile_uis_�� �߰�
	void LoadTileListFromTexture(UINT page);//TileEditUi���� TileUi�� ������ ��� �۾�
	void ChangePage(UINT page);
	void PickTileUi(int tile_ui_idx);

public:
	void Init();
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;

	void ChangeMode(TILE_EDIT_MODE mode);
	void ChangeTileuisTexture(Texture* tileuis_texture, Vector2 texture_base_pos, Vector2 texture_scale, Vector2 sprite_scale, Vector2 interval, int count);

	inline void set_director(Director_Scene_Tool* director) { director_ = director; };
	inline ButtonUi** get_mode_buttons() { return mode_buttons_; };
	inline TileUi* get_picked_tile_ui() { return picked_tile_ui_; };
	inline UINT get_page() { return page_; };
	inline TILE_EDIT_MODE get_mode() { return mode_; };
	inline UINT get_max_col() {
		return tile_ui_sprites_[0]->get_texture()->get_width() / tile_ui_sprites_[0]->get_scale().x; //static_cast<int>((get_scale().x - TILE_UI_BASE_POS_X * 2) / TILE_UI_SCALE_X);
	}
	inline UINT get_max_row() {
		return static_cast<int>((get_scale().y - TILE_UI_BASE_POS_Y * 2) / TILE_UI_SCALE_Y);
	}
};

