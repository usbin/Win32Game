#pragma once
#include "PanelUi.h"
#include "Texture.h"
class TileUi;
class Director_Scene_Tool;
class ButtonUi;
class Sprite;



class TileEditUi : public PanelUi
{
public:
	TileEditUi();
	~TileEditUi();
private:
	Director_Scene_Tool* director_;

	ButtonUi* mode_buttons_[static_cast<ULONGLONG>(TILE_EDIT_MODE::END)];

	std::vector<TileUi*> tile_uis_;
	std::vector<Sprite*> tile_ui_sprites_;

	TileUi* picked_tile_ui_;
	UINT page_;

	void CreateExitBtn();
	void CreateAddModeBtn();

	void CreateColliderModeBtn();
	void CreateArrowBtns();
	void CreateEmptyTileUis();
	//texture에서 TileUi들을 생성하고 tile_uis_에 추가
	void AddTileListFromTexture(Texture* texture, const Vector2& texture_base_pos, const Vector2& texture_scale
		, const Vector2& sprite_scale, const Vector2& interval, int count);
	//TileEditUi위에 TileUi를 실제로 얹는 작업
	void LoadTileListFromTexture(UINT page);

	void ChangePage(UINT page);

public:
	void Init();

	inline void set_director(Director_Scene_Tool* director) { director_ = director; };
	inline ButtonUi** get_mode_buttons() { return mode_buttons_; };
	inline TileUi* get_picked_tile_ui() { return picked_tile_ui_; };
	inline UINT get_page() { return page_; };
	
	void PickTileUi(TileUi* tile_ui);
};

