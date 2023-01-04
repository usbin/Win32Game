#include "Background_Title.h"
#include "UiAnimator.h"
#include "Animation.h"
#include "Core.h"
#include "ResManager.h"
#include "Texture.h"
#include "UiSprite.h"

Background_Title::Background_Title()
	:Ui(true)
{
	Vector2 bg_size = Core::GetInstance()->get_resolution();
	Texture* bg_texture = ResManager::GetInstance()->LoadTexture(_T("Title Background"), _T("texture\\title_bg.png"));
	Vector2 bg_img_size = bg_texture->get_size();

	Animator* animator = DEBUG_NEW UiAnimator();
	animator->set_owner(this);
	set_animator(animator);
	animator->CreateAnimation(_T("Title Background Animation"), bg_texture, Vector2(0, 0), Vector2(bg_img_size.x, ((bg_size.y / bg_size.x) * bg_img_size.x)), Vector2(0, 1), Vector2(0, 0), 0.025f, 200, false);
	animator->Play(_T("Title Background Animation"));

	UiSprite* sprite = DEBUG_NEW UiSprite();
	sprite->QuickSet(bg_texture, this, Vector2(0, 200), Vector2(bg_img_size.x, ((bg_size.y / bg_size.x) * bg_img_size.x)));
	sprite->set_owner(this);
	ChangeSprite(sprite);

	

}

Background_Title::~Background_Title()
{
}

void Background_Title::Update()
{
	Ui::Update();
	ChildrenUpdate();
}

void Background_Title::Render(ID3D11Device* p_d3d_device)
{
	if (get_enabled()) {
		Vector2 pos = get_final_pos();
		if (!is_static_pos()) pos = WorldToRenderPos(pos);
		const Vector2& scale = get_scale();
		if (!IsAnimationDone()) {
			get_animator()->Render(p_d3d_device);
		}
		else {
			if (get_sprite()) {

				Texture* texture = get_sprite()->get_texture();
				const Vector2& sprite_base_pos = get_sprite()->get_base_pos();
				const Vector2& sprite_scale = get_sprite()->get_scale();
				DrawTexture(p_d3d_device, pos, scale, sprite_base_pos, sprite_scale, texture);
			}
		}
	}


	ChildrenRender(p_d3d_device);
}

bool Background_Title::IsAnimationDone()
{

	Animator* animator = get_animator();
	if (!animator) return true;

	Animation* bg_animation = animator->FindAnimation(_T("Title Background Animation"));
	if (!bg_animation) return true;
	
	return bg_animation->is_finished();
}
