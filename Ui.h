#pragma once
#include "GObject.h"
#include "UiManager.h"
#include "IFrame.h"
class GObjectSprite;

typedef void (*OnClickHandler)(DWORD_PTR param1, DWORD_PTR param2);
struct OnClickHandlerParams {
	OnClickHandler on_click;
	DWORD_PTR param1;
	DWORD_PTR param2;
};

class Ui : public GObject
{
public:
	Ui(bool is_static_pos);
	virtual ~Ui();
private:
	bool is_static_pos_ = false;		// 카메라에 영향받지 않는 좌표계를 쓰는가(일반적인 Ui처럼 위치 고정)
	Vector2 final_pos_ = Vector2::Zero();
	Ui* parent_ = nullptr;				// 이 ui가 자식으로 있는 ui. root ui일 경우 nullptr.
	std::vector<Ui*> children_;	// 이 ui 위에 있는 child ui. 

	GObjectSprite* sprite_ = nullptr;
	Animator* animator_ = nullptr;


	bool mouse_on_check_ = false;				// 위에 다른 ui가 있든 말든 단순 좌표만으로 체크함
	bool lbutton_hold_ = false;			// 가장 위에서 실제로 이벤트를 받았을 때에만 체크됨.

	bool selectable_ = false;			// "선택됨" 상태가 가능한지
	bool is_selected_ = false;




public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(ID3D11Device* p_d3d_device);
protected:
	virtual void ChildrenUpdate() final;
	virtual void ChildrenFinalUpdate() final;
	virtual void ChildrenRender(ID3D11Device* p_d3d_device) final;


	inline std::vector<Ui*>& get_children_unsafe() { return children_; };


public:
	virtual void MouseOn() {};
	virtual void LbuttonClick() {};
	virtual void LbuttonDown() {};
	virtual void LbuttonUp() {};
	virtual void Select() { };
	virtual void Unselect() { };
	
	GObjectSprite* get_sprite() { return sprite_; };
	virtual void ChangeSprite(GObjectSprite* sprite);

	inline void set_animator(Animator* animator) { animator_ = animator; };
	inline Animator* get_animator() { return animator_; };

	inline void AddChild(Ui* child) { children_.push_back(child); };
	inline const std::vector<Ui*>& get_children() { return children_; };
	inline bool	is_static_pos() { return is_static_pos_; };
	inline const Vector2& get_final_pos() { return final_pos_; };
	inline Ui* get_parent() { return parent_; };
	inline void set_parent(Ui* parent) { parent_ = parent; };
	inline bool get_mouse_on() { return mouse_on_check_; };
	inline bool get_lbutton_hold() { return lbutton_hold_; };
	inline void set_lbutton_hold(bool b) { lbutton_hold_ = b; };
	inline bool get_is_selectable() { return selectable_; };
	inline void set_is_selectable(bool b) { selectable_ = b; };
	inline bool get_selected() { return is_selected_; };
	inline void set_selected(bool b) { is_selected_ = b; };
	void OnEnabled(bool b) override;

private:

	friend class UiManager;
};

