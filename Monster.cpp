#include "Monster.h"
#include "Time.h"
#include "Collider.h"
#include "SelectGdi.h"

Monster::Monster()
	: move_speed_(200.f)
	, center_pos_(Vector2{0,0})
	, direction_(-1)
	, move_range_(0){
	Collider* collider = new Collider();
	collider->set_owner(this);
	collider->set_scale(Vector2{ 20, 20 });
	set_collider(collider);
}
Monster::~Monster() {};
void Monster::Update()
{
	//매 프레임 center-100에 도달할 때까지 pos.x-= move_speed_*dt
	//도달하면 center+100에 도달할 때까지 posx+= move_speed_*dt
	Vector2 pos = get_pos();
	if (abs(center_pos_.x - pos.x) > move_range_) {
		//가장자리로 바로잡기
		pos.x = center_pos_.x + direction_ * move_range_;
		direction_ *= -1;
	}
	pos.x = static_cast<float>(static_cast<double>(pos.x) + 
		static_cast<double>(direction_) * static_cast<double>(move_speed_) * Time::GetInstance()->dt_f());
	set_pos(pos);
}

void Monster::Render(ID3D11Device* p_d3d_device) {
	RealObject::Render(p_d3d_device);

	Vector2 render_pos = WorldToRenderPos(get_pos());

	DrawRectangle(p_d3d_device, render_pos-get_scale()/2.f, get_scale(), ARGB(0xFF000000));


	const TCHAR* text = _T("Hello, world!");
	DrawAutosizeText(p_d3d_device, render_pos, Vector2(10, 10), text, _tcslen(text), _T("둥근모꼴"), D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_FAR,
		30, 15, 3);
	//DrawFixedsizeText(p_d3d_device, pos, scale, text, _tcslen(text), _T("둥근모꼴"), 20, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_FAR);


	ComponentRender(p_d3d_device);

}
