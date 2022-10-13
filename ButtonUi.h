#pragma once
//ButtonUi는 외부에서 클릭 이벤트 핸들러 등록 가능.
#include "global.h"
#include "Ui.h"
typedef void (*OnClickHandler)(DWORD_PTR param1, DWORD_PTR param2);
struct OnClickHandlerParams {
	OnClickHandler on_click;
	DWORD_PTR param1;
	DWORD_PTR param2;
};
class ButtonUi : public Ui
{
public:
	ButtonUi(bool is_static_pos);
	~ButtonUi();
private:
	// OnClick 핸들러 함수들
	std::vector<OnClickHandlerParams> on_click_handler;
	bool is_selected_;

public:
	virtual void Render(HDC hdc) override;
	virtual void MouseOn() override;
	virtual void LbuttonClick() override;
	virtual void LbuttonDown() override;
	virtual void LbuttonUp() override;
	void AddOnClickHandler(OnClickHandler on_click, DWORD_PTR param1, DWORD_PTR param2);

	inline bool selected() { return is_selected_; };
	inline void set_selected(bool b) { is_selected_ = b; };
};

