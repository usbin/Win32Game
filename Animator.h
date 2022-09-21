#pragma once
#include "global.h"
class Animation;
class Texture;
class Animator
{
public:
	Animator();
	Animator(const Animator& origin);
	~Animator();
private:
	GObject* owner_;
	std::map<tstring, Animation*> anims_;
	Animation* current_anim_;
public:
	void CreateAnimation(const tstring& name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset
		,float duration, int img_count, bool is_repeat);
	void Play(const tstring& name);
	Animation* FindAnimation(const tstring& name);
	void Update();
	void Render(HDC hdc);

	GObject* get_owner() { return owner_; };
private :
	void set_owner(GObject* owner) { owner_ = owner; };


	friend class GObject;
	friend class Player;
};

