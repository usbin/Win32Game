#pragma once
#include "GObject.h"
class Ui : public GObject
{
public:
	Ui(bool is_static_pos);
	~Ui();
private:
	bool is_static_pos_;		// 카메라에 영향받지 않는 좌표계를 쓰는가(일반적인 Ui처럼 위치 고정)
	Vector2 final_pos_;
	Ui* parent_;				// 이 ui가 자식으로 있는 ui. root ui일 경우 nullptr.
	std::vector<Ui*> children_;	// 이 ui 위에 있는 child ui. 


	bool mouse_on_;				// 위에 다른 ui가 있든 말든 단순 좌표만으로 체크함

	bool lbutton_hold_;			// 가장 위에서 실제로 이벤트를 받았을 때에만 체크됨.



public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC hdc) = 0;
protected:
	virtual void ChildrenUpdate() final;
	virtual void ChildrenFinalUpdate() final;
	virtual void ChildrenRender(HDC hdc) final;



public:
	virtual void MouseOn()=0;
	virtual void MouseClick()=0;
	virtual void MouseDown()=0;
	virtual void MouseUp()=0;


	inline void AddChild(Ui* child) { children_.push_back(child); };
	inline const std::vector<Ui*>& get_children() { return children_; };
	inline bool	is_static_pos() { return is_static_pos_; };
	inline const Vector2& get_final_pos() { return final_pos_; };
	inline Ui* get_parent() { return parent_; };
	inline void set_parent(Ui* parent) { parent_ = parent; };
	inline bool get_mouse_on() { return mouse_on_; };
	inline bool get_lbutton_hold() { return lbutton_hold_; };
	inline void set_lbutton_hold(bool b) { lbutton_hold_ = b; };
};

