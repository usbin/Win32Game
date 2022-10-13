#pragma once
#include "GObject.h"
class Ui : public GObject
{
public:
	Ui(bool is_static_pos);
	~Ui();
private:
	bool is_static_pos_;		// ī�޶� ������� �ʴ� ��ǥ�踦 ���°�(�Ϲ����� Uió�� ��ġ ����)
	Vector2 final_pos_;
	Ui* parent_;				// �� ui�� �ڽ����� �ִ� ui. root ui�� ��� nullptr.
	std::vector<Ui*> children_;	// �� ui ���� �ִ� child ui. 


	bool mouse_on_check_;				// ���� �ٸ� ui�� �ֵ� ���� �ܼ� ��ǥ������ üũ��

	bool lbutton_hold_;			// ���� ������ ������ �̺�Ʈ�� �޾��� ������ üũ��.




public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC hdc);
protected:
	virtual void ChildrenUpdate() final;
	virtual void ChildrenFinalUpdate() final;
	virtual void ChildrenRender(HDC hdc) final;


	inline std::vector<Ui*>& get_children_unsafe() { return children_; };


public:
	virtual void MouseOn() {};
	virtual void LbuttonClick() {};
	virtual void LbuttonDown() {};
	virtual void LbuttonUp() {};


	inline void AddChild(Ui* child) { children_.push_back(child); };
	inline const std::vector<Ui*>& get_children() { return children_; };
	inline bool	is_static_pos() { return is_static_pos_; };
	inline const Vector2& get_final_pos() { return final_pos_; };
	inline Ui* get_parent() { return parent_; };
	inline void set_parent(Ui* parent) { parent_ = parent; };
	inline bool get_mouse_on() { return mouse_on_check_; };
	inline bool get_lbutton_hold() { return lbutton_hold_; };
	inline void set_lbutton_hold(bool b) { lbutton_hold_ = b; };
};

